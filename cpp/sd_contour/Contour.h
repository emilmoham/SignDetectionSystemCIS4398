#ifndef CONTOURDRAWING_H
#define CONTOURDRAWING_H

#include "../headers/OpenCVHeaders.h"

using namespace cv;
using namespace std;

std::vector<std::vector<cv::Point> > sd_getContours(cv::Mat mat);

#endif
