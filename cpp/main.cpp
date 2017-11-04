/**
 * Simple shape detector program.
 * It loads an image and tries to find simple shapes (rectangle, triangle, circle, etc) in it.
 * This program is a modified version of `squares.cpp` found in the OpenCV sample dir.
 */
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/**
 * Helper function to display text in the center of a contour
 */
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;
    
    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
    
    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

int main()
{
    
  //VideoCapture cap(0);
  //if(!cap.isOpened()){  // check if we succeeded
  //  std::cout << "Failed" << endl;	//Print if we failed
  //    return -1;
  //}
    
    cv::Mat src = cv::imread("road-signs.jpg", CV_LOAD_IMAGE_COLOR);
    //cv::Mat src = cv::imread("all.jpg");
    if(!src.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
    for(;;){
    
        // Convert to grayscale
        Mat frameFromVideo;
        //cap >> frameFromVideo; // get a new frame from camera
	frameFromVideo = src;
        cv::Mat gray;
        cv::cvtColor(frameFromVideo, gray, CV_BGR2GRAY);
        
        // Use Canny instead of threshold to catch squares with gradient shading
        cv::Mat bw;
        GaussianBlur(gray, bw, Size(19,19), 1.5, 1.5);
        cv::Canny(gray, bw, 0, 100, 3);
        
        // Find contours
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        std::vector<cv::Point> approx;
        cv::Mat dst = frameFromVideo.clone();
        
        for (int i = 0; i < contours.size(); i++)
        {
            // Approximate contour with accuracy proportional
            // to the contour perimeter
            cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
            
            // Skip small or non-convex objects
            if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
                continue;
            
            if (approx.size() == 3)
            {
                setLabel(dst, "TRI", contours[i]);    // Triangles
            }
            else if (approx.size() >= 4 && approx.size() <= 6)
            {
                // Number of vertices of polygonal curve
                int vtc = int(approx.size());
                
                // Get the cosines of all corners
                std::vector<double> cos;
                for (int j = 2; j < vtc+1; j++)
                    cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));
                
                // Sort ascending the cosine values
                std::sort(cos.begin(), cos.end());
                
                // Get the lowest and the highest cosine
                double mincos = cos.front();
                double maxcos = cos.back();
                
                // Use the degrees obtained above and the number of vertices
                // to determine the shape of the contour
                if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
                    setLabel(dst, "RECT", contours[i]);
                else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
                    setLabel(dst, "PENTA", contours[i]);
                else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
                    setLabel(dst, "HEXA", contours[i]);
            }
            else
            {
                // Detect and label circles
                double area = cv::contourArea(contours[i]);
                cv::Rect r = cv::boundingRect(contours[i]);
                int radius = r.width / 2;
                
                if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                    std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
                    setLabel(dst, "CIR", contours[i]);
            }
        }


	// drawing contours
	for( int i = 0; i< contours.size(); i++ )
	{
	  Scalar color = Scalar( 255, 255, 0 );
	  //approxPolyDP(Mat(contours[i]), contours[i], 3, true);
	  drawContours( dst, contours, i, color, 2);
	}
	
        cv::imshow("src", frameFromVideo);
        cv::imshow("dst", dst);
        
        if(waitKey(30) >= 0)		//This goes here to work
            break;
    
    }
    
    return 0;
}
