#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>

#include "Render.h"

using namespace cv;
using namespace std;

void sd_drawContours(cv::Mat& im, vector<vector<Point> > contours){
    // Draw contours
    for( int i = 0; i< contours.size(); i++ ) {
        Scalar color = Scalar( 0, 0, 255 );
        //approxPolyDP(Mat(contours[i]), contours[i], 3, true);
        drawContours( im, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
}

void sd_labelShape(vc::Mat& im, int shape, std::vector<cv::Point>& contour){
            switch(shape){
	    case 10: sd_setLabel(dst, "CIR", contours[i]);
	      break;
	    case 30: sd_setLabel(dst, "TRI", contours[i]);
	      break;
	    case 40: sd_setLabel(dst, "RECT", contours[i]);
	      break;
	    case 50: sd_setLabel(dst, "PENTA", contours[i]);
	      break;
	    case 60: sd_setLabel(dst, "HEXA", contours[i]);
	      break;
	    case 80: sd_setLabel(dst, "OCTO", contours[i]);
	      break;
	    }
}

void sd_setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
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

void sd_drawBoundingBox(cv::Mat& im, std::vector<cv::Point>& contour){
  // TODO draw bounding box
}
