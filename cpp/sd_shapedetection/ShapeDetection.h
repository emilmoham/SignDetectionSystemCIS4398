#ifndef SHAPEDETECTION_H
#define SHAPEDETECTION_H

#include "../headers/OpenCVHeaders.h"

using namespace cv;
using namespace std;

int sd_getShape(std::vector<cv::Point> approx, std::vector<cv::Point> contour);

#endif
