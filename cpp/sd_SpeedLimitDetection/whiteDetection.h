#ifndef WHITE_DETECTION_H
#define WHITE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>

using namespace cv;
//using namespace std;

RNG rng(12345);

Mat1b find_white(Mat3b bgr){
    Mat3b scaled_image;
    Mat3b blurred_image;
    Mat3b hsv;
    Mat1b mask1, mask2;


    //Blur image to blend colors
    GaussianBlur(bgr/*scaled_image*/, blurred_image, Size(9,9), 0);

    //Change color encoding to HSV
    cvtColor(blurred_image, hsv, COLOR_BGR2HSV);

    //Create masks by filtering red colors
    inRange(hsv, Scalar(0, 0, 245), Scalar(255, 0, 255), mask1); //white

    //Combine masks to create a single mask

    //Return mask information
    return mask1;
}

Mat outline_shapes(Mat src, Mat1b mask){
    Mat bw;

    Canny(mask, bw, 0, 50, 5);

    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    std::vector<cv::Point> approx;
    cv::Mat dst = src.clone();

    for (int i = 0; i < contours.size(); i++){
        Scalar color = Scalar( rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0,255));

        // Approximate contour with accuracy proportional
        // to the contour perimeter
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
        continue;

        if (approx.size() == 3)
        {
            //setLabel(dst, "TRI", contours[i]);    // Triangles
        }
        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();

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
            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3){
            	setLabel(dst, "SPEED LIMIT", contours[i]);
		//drawContours( src, contours, i, color, 
	    }
            else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27){}
            //setLabel(dst, "PENTA", contours[i]);
            else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45){}
            //setLabel(dst, "HEXA", contours[i]);
        } else if (approx.size() == 8){
            setLabel(dst, "STOP", contours[i]);
            drawContours( src, contours, i, color, 2, 8, approx, 0, Point());
        } else {
            // Detect and label circles
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);
            int radius = r.width / 2;

            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
            std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2){}
            //setLabel(dst, "CIR", contours[i]);
        }
    }
    return dst;
}

#endif
