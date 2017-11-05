/**
 * Simple shape detector program.
 * It loads an image and tries to find simple shapes (rectangle, triangle, circle, etc) in it.
 * This program is a modified version of `squares.cpp` found in the OpenCV sample dir.
 */
#include "../headers/OpenCVHeaders.h"
#include <cmath>

#include "Contour.h"
#include "../sd_shapedetection/ShapeDetection.h"
#include "../sd_render/Render.h"

using namespace cv;
using namespace std;

int main()
{   
    cv::Mat src = cv::imread("road-signs.jpg", CV_LOAD_IMAGE_COLOR);
    if(!src.data ) {                 // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    for(;;){
        std::vector<std::vector<cv::Point> > contours;
        contours = sd_getContours(src);
        std::vector<cv::Point> approx;
        cv::Mat dst = src.clone();
        
        for (int i = 0; i < contours.size(); i++)
        {
            // Approximate contour with accuracy proportional
            // to the contour perimeter
            cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
            
            // Skip small or non-convex objects
            if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
                continue;

	    int shape = sd_getShape(approx, contours[i]);

	    sd_labelShape(dst, shape, contours[i]);
        }

	// drawing contours
	for( int i = 0; i< contours.size(); i++ ) {
	  sd_drawContours(dst, contours);
	}
	
        cv::imshow("src", src);
        cv::imshow("dst", dst);
        
        if(waitKey(30) >= 0)		//This goes here to work
            break;
    }
    
    return 0;
}
