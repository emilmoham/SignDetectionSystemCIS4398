#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>

#include "ShapeDetection.h"

using namespace cv;
using namespace std;

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

int sd_getShape(std::vector<cv::Point> approx, std::vector<cv::Point> contour){
	if (approx.size() == 3)
            {
                return 30; // TRIANGLE
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
                    return 40; // RECTANGLE
                else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
                    return 50; // PENTAGON
                else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
                    return 60; // HEXAGON
            }
            else
            {
                // Detect and label circles
                double area = cv::contourArea(contour);
                cv::Rect r = cv::boundingRect(contour);
                int radius = r.width / 2;
                
                if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                    std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
                    return 10; // CIRCLE
            }
}
