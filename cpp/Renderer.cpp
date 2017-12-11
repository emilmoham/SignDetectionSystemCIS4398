#include "Renderer.h"
#include "NodeID.h"
#include "FrameResult.h"
#include "LogHelper.h"

#include <opencv2/opencv.hpp>
#include <mpi.h>

void Renderer::setOutputMode(OutputMode mode)
{
    m_outputMode = mode;
}

void Renderer::run()
{
    // Get fps, width, height of video
    int buffer[3];
    MPI_Recv(&buffer[0], 3, MPI_INT, MASTER_ID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

    FrameResult fr;

    char c = '\0';
    cv::namedWindow("Detected Signs", 1);

    // Open output file
    cv::VideoWriter writer;
    writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), buffer[0], cv::Size(buffer[1], buffer[2]), true); 
    if (!writer.isOpened())
        LOG_ERROR("output", "Could not open output file");

    int analysisBuffer[2];
    while (c != 27) 
    {
        fr.receive(MASTER_ID);
        
        // Get analyzer results
        MPI_Recv(&analysisBuffer, 2, MPI_INT, ANALYZER_A, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (analysisBuffer[0] == fr.frame.index && analysisBuffer[1] > 0)
        {
            Region r;
            r.receive(ANALYZER_A);
            fr.regions.push_back(std::move(r));
        }
        MPI_Recv(&analysisBuffer, 2, MPI_INT, ANALYZER_B, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (analysisBuffer[0] == fr.frame.index && analysisBuffer[1] > 0)
        {
            Region r;
            r.receive(ANALYZER_B);
            fr.regions.push_back(std::move(r));
        }
        MPI_Recv(&analysisBuffer, 2, MPI_INT, ANALYZER_C, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (analysisBuffer[0] == fr.frame.index && analysisBuffer[1] > 0)
        {
            Region r;
            r.receive(ANALYZER_C);
            fr.regions.push_back(std::move(r));
        }

        renderFrameResult(fr);

        c = cv::waitKey(40);
        writer.write(fr.frame.cvFrame);
    }

    writer.release();
}

void Renderer::renderFrameResult(FrameResult &fr)
{
    /* Fixed output mode: on screen while saving to file
    switch(m_outputMode){
        default: debugVisual(fr); break;
    }
    */

    cv::Scalar color = cv::Scalar(124, 252, 0);
    int i = 1;
    for (const auto &r : fr.regions)
    {
        std::string signText;
        for (const auto &rect : r.rects)
            cv::rectangle(fr.frame.cvFrame, rect.tl(), rect.br(), color, 2, 8, 0);
        
        if (r.signText.empty())
        {
            switch (r.signType)
            {
                case STOP_SIGN:
                    signText = "Stop";
                    break;
                case YIELD_SIGN:
                    signText = "Yield";
                    break;
                case WARNING_SIGN:
                    signText = "Warning";
                    break;
                case SPEED_LIMIT:
                    signText = "Speed Limit";
                    break;
                default: break;
            }
        }
        else
            signText = r.signText;

        if (!signText.empty())
        {
            cv::putText(fr.frame.cvFrame, signText, cvPoint(30 * i, 30 * i), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2,
                cvScalar(0, 0, 0), 1, CV_AA);
	    ++i;
        }

        cv::imshow("Detected Signs", fr.frame.cvFrame);
    }

}
