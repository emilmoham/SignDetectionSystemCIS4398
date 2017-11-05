#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include "headers/pack_region.h"

using namespace cv;
using namespace std;

public Region packRegion(vector<Point> contour, int shape, int color){
    return new Region(contour, shape, color);
}
