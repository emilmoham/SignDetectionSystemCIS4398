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
  Scalar color = Scalar( 128, 255, 0 );
    for( int i = 0; i< contours.size(); i++ ) {
        drawContours( im, contours, i, color, 2 );
    }
}

void sd_labelShape(cv::Mat& im, int shape, std::vector<cv::Point>& contour){
            switch(shape){
	    case 10: sd_setLabel(im, "CIR", contour);
	      break;
	    case 30: sd_setLabel(im, "TRI", contour);
	      break;
	    case 40: sd_setLabel(im, "RECT", contour);
	      break;
	    case 50: sd_setLabel(im, "PENTA", contour);
	      break;
	    case 60: sd_setLabel(im, "HEXA", contour);
	      break;
	    case 80: sd_setLabel(im, "OCTO", contour);
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
