#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int checkArguments(int argc, char **argv);
void showImage(char *path);
void find_red(char *path);

int main(int argc, char **argv){
    //Check if user has supplied an imagefile to the program
    if(!checkArguments(argc, argv)){
        return -1;
    }

    find_red(argv[1]);

    return 0;
}

int checkArguments(int argc, char **argv){
    if(argc < 2){
        printf("Usage %s <picture_path>\n", argv[0]);
        return 0;
    }
    return 1;
}

void showImage(char *path){
    Mat image_BGR, image_RGB;

    //Read Image into Mat Object
    image_RGB = imread( path, IMREAD_COLOR);
    //cvtColor(image_BGR,image_RGB,CV_RGB2BGR);

    namedWindow( path, WINDOW_AUTOSIZE);
    imshow( path, image_RGB);

    waitKey(0);
}

void find_red(char *path){
    Mat src, rgb_image, scaled_image, blurred_image, hsv_image;
    double scale;
    int max_dimension;

    src = imread(path);
    cvtColor(src, rgb_image, CV_BGR2RGB);
    max_dimension = max(rgb_image.cols, rgb_image.rows);
    scale = 700.0/max_dimension;

    resize(rgb_image, scaled_image, Size(), scale, scale);

    GaussianBlur(scaled_image, blurred_image, Size(7,7), 0);

    cvtColor(blurred_image, hsv_image, CV_RGB2HSV);

    namedWindow("previous", WINDOW_AUTOSIZE);
    imshow("previous", blurred_image);
    namedWindow("latest", WINDOW_AUTOSIZE);
    imshow("latest", hsv_image);

    waitKey(0);
}

/*
See https://stackoverflow.com/questions/32522989/opencv-better-detection-of-red-color
*/
