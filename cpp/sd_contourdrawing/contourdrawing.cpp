//
//  main.cpp
//  ShapeDetection
//
//  Created by Michael Donahue on 11/3/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

RNG rng(12345);

int main( int argc, char** argv )
{
    Mat image, bwImage, output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    image = imread("road-signs.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
    cvtColor(image, bwImage, cv::COLOR_BGR2GRAY);   //Convert to grayscale
    GaussianBlur(bwImage, bwImage, Size(7,7), 1.5, 1.5);
    Canny(bwImage, bwImage, 0, 30, 3);
    findContours(bwImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    
    
    /// Draw contours
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //approxPolyDP(Mat(contours[i]), contours[i], 3, true);
        drawContours( image, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }

    
    
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
