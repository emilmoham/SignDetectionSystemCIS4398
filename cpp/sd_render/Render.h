#ifndef RENDER_H
#define RENDER_H

#include "../headers/OpenCVHeaders.h"

using namespace cv;
using namespace std;

void sd_drawContours(cv::Mat& im, vector<vector<Point> > contours);

void sd_labelShape(cv::Mat& im, int shape, std::vector<cv::Point>& contour);

void sd_setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);

void sd_drawBoundingBox(cv::Mat& im, std::vector<cv::Point>& contour);

#endif
