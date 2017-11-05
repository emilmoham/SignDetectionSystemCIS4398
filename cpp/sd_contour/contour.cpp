#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>

#include "Contour.h"

using namespace cv;
using namespace std;

std::vector<std::vector<cv::Point> > sd_getContours(cv::Mat image){
    Mat bwImage, output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
  
    cvtColor(image, bwImage, cv::COLOR_BGR2GRAY);   //Convert to grayscale
    GaussianBlur(bwImage, bwImage, Size(7,7), 1.5, 1.5);
    Canny(bwImage, bwImage, 0, 30, 3);
    findContours(bwImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    return contours;
}
