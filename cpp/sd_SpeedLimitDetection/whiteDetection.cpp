#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include "speedlimit_modifiedShapeDetection.h"
#include "whiteDetection.h"

using namespace cv;

int checkArguments(int argc, char **argv){
    if(argc < 2){
        std::printf("Usage %s <stream_path>\n", argv[0]);
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int i;
    Mat frame;
    Mat processed;
    Mat1b white_mask;

    int frame_counter = 0;

    //Checking to see if a path was supplied
    if(!checkArguments(argc, argv)){
        return -1;
    }

    VideoCapture cap(argv[1]);//Video or Image
    if( ((std::string)argv[1]).compare("0") == 0){
        cap.open(0);//Webcam
    }

    if( !cap.isOpened() )
        throw "Error when reading steam_avi";

    namedWindow( "w", 1);

    for (i = 0;i < 1000;i++){
        cap >> frame;

        white_mask = find_white(frame);

        processed = outline_shapes(frame, white_mask);


        //if(++frame_counter % 4 == 0){
            //imshow("w", red_mask);
            imshow("x", processed);
            waitKey(33);
        //}
    }
    //waitKey();

    return 0;
}
