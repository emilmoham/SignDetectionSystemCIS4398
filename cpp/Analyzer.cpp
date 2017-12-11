#include "Analyzer.h"
#include "Colors.h"
#include "NodeID.h"
#include "SignType.h"
#include <cmath>
#include <mpi.h>

void Analyzer::run()
{
    FrameResult frameRes;
    int metaData[3];
    MPI_Recv(&metaData[0], 3, MPI_INT, MASTER_ID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    m_width = metaData[1];
    m_height = metaData[2];

    int buffer[2];
    for (;;)
    {
        frameRes.receive(MASTER_ID);
        getSignInformation(frameRes);

        // Package results for renderer (frame index, number regions detected with signs) 
        buffer[0] = frameRes.frame.index;
        buffer[1] = static_cast<int>(frameRes.regions.size());

        MPI_Send(&buffer, 2, MPI_INT, RENDERER_ID, 0, MPI_COMM_WORLD);
        if (buffer[1] > 0)
            frameRes.regions.at(0).send(RENDERER_ID);
    }
}

void Analyzer::setColorMask(ColorMask mask)
{
    m_colorMask = mask;
}

void Analyzer::getSignInformation(FrameResult &frameResult)
{
    // Clear previous frame data
    m_region.cvContours.clear();
    m_region.hierarchy.clear();
    m_region.rects.clear();
    m_regionPoly.cvContours.clear();
    m_regionPoly.hierarchy.clear();
    m_regionPoly.rects.clear();
    m_approx.clear();

    // Instantiate Region to be added to frame result
    Region resultRegion;

    cv::Mat converted = frameResult.frame.cvFrame.clone();
    cvtColor(converted, converted, cv::COLOR_BGR2HSV);

    cv::Mat finalMat;
    double largestArea = 0.0, largestAreaThresh = 0.0, smallestAreaThresh = 0.0; ratio = 0.0;
    int largestContourIndex = 0;
    int minContours = 0, maxContours = 0;

    switch (m_colorMask)
    {
        case ColorMask::Red:
        {
            resultRegion.colors = Color::Red;
            minContours = 2;
            maxContours = 7;
	    smallestAreaThresh = 10000.0;
            largestAreaThresh = 60.0;
            cv::Mat red1, red2;
            inRange(converted, cv::Scalar(0, 80, 80), cv::Scalar(10, 255, 255), red1);    //Low end of red mask
            inRange(converted, cv::Scalar(170, 80, 80), cv::Scalar(180, 255, 255), red2); //High end of red mask
            finalMat = red1 | red2;
            break;
        }
        case ColorMask::Yellow:
        {
            resultRegion.colors = Color::Yellow;
            minContours = 2;
            maxContours = 6;
	    smallestAreaThresh = 10000.0;
            largestAreaThresh = 20.0;
            inRange(converted, cv::Scalar(25, 150, 150), cv::Scalar(30, 255, 255), finalMat);
            break;
        }
        case ColorMask::White:
        {
	    /*
	     * Seems to crash without min and max contours > 0
	     */
            resultRegion.colors = Color::White;
            minContours = 3;
            maxContours = 5;
	    smallestAreaThresh = 800.0
            largestAreaThresh = 300.0;
            inRange(converted, cv::Scalar(0, 0, 210), cv::Scalar(255, 50, 255), finalMat);
            break;
        }
        default:
            break;
    }

    // Edge pre-processing (same for each color mask)
    cv::GaussianBlur(finalMat, finalMat, cv::Size(9,9), 1.5, 1.5);                    //Blur mask
    cv::threshold(finalMat, finalMat, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);        //Threshold mask

    // Find and draw contours in mask
    cv::findContours(finalMat, m_region.cvContours, m_region.hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);

    int numContours = m_region.cvContours.size();

    m_regionPoly.cvContours.resize(numContours);
    m_regionPoly.rects.resize(numContours);

    // Iterate through contours and draw edges around positively detected regions
    for (int i = 0; i < numContours; ++i)
    {
        cv::approxPolyDP(cv::Mat(m_region.cvContours[i]), m_approx, cv::arcLength(cv::Mat(m_region.cvContours[i]), true) * 0.02, true);
        cv::approxPolyDP(cv::Mat(m_region.cvContours[i]), m_regionPoly.cvContours[i], 3, true);
        m_regionPoly.rects[i] = cv::boundingRect(cv::Mat(m_regionPoly.cvContours[i]));

        // Skip small regions
        if ((fabs(cv::contourArea(m_region.cvContours[i])) < 300)  || !cv::isContourConvex(m_approx))
        {
            continue;
        }
        else
        {
            auto approxSize = m_approx.size();
            bool ratioOk = (m_colorMask == ColorMask::Red);
            if (m_colorMask == ColorMask::Yellow) // || m_colorMask == ColorMask::White)
            {
		ratio = m_regionPoly.rects[i].height / m_regionPoly.rects[i].width;
		if (ratio > 0.8 && ratio < 1.2)
		{
			ratioOk = true;
		} 
            }
	    if (m_colorMask == ColorMask::White)
	    {
		ratio = m_regionPoly.rects[i].height / m_regionPoly.rects[i].width;
		if (ratio >= 0.99 && ratio <= 1.01)
		{
			ratioOk = true;
		}
	    }
            const bool hasContoursForSign = ((approxSize > minContours) && (approxSize < maxContours));
            const bool hasContoursForStopSign = (m_colorMask == ColorMask::Red && approxSize > maxContours && approxSize < 10);
            if (ratioOk && (hasContoursForSign || hasContoursForStopSign)) 
            {
                // Find area of contour
                double a = cv::contourArea(m_region.cvContours[i], false);

                // Check if contour is the largest found within the color masked frame. If so, it's probably a sign.
                if (a > largestArea)
                {
                    largestArea = a;
                    if (largestArea > largestAreaThresh && largestArea < smallestAreaThresh)
                    {
                        largestContourIndex = i;

                        // Store sign information in resultRegion
                        resultRegion.rects.push_back(m_regionPoly.rects[i]);

                        SignType sign = INVALID_SIGN;
                        if (hasContoursForStopSign)
                            sign = STOP_SIGN;
                        else 
                        {
                            switch (m_colorMask)
                            {
                                case ColorMask::Red:    sign = YIELD_SIGN;   break;
                                case ColorMask::Yellow: sign = WARNING_SIGN; break;
                                case ColorMask::White:  sign = SPEED_LIMIT;  break;
                                default: break;
                            }
                        }

                        // Extract text from sign region
                        if (sign != INVALID_SIGN)
                        {
			    auto &rect = m_regionPoly.rects[i];
			    if (rect.width >= m_width / 10) 
                            	resultRegion.signText = m_textExtractor.getText(frameResult.frame.cvFrame(m_regionPoly.rects[i]));
                        }

                        resultRegion.signType = sign;
                        largestArea = 0.0;
                    }
                }
            }
        }
    }

    frameResult.regions.push_back(resultRegion);
}

