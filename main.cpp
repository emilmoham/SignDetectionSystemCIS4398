#include <iostream>
#include "stdafx.h"
#include <cv.h>
#include <highgui.h>

using namespace cv;

Mat img, gray_img, output_img;

int thresh = 100;
int max_thresh = 255;

int main() {

    img  = imread("signs.jpg");
    cvtColor(img,gray_img,CV_RGB2GRAY);
    imshow("InputImage",img);


    CvSeq* contour;  //hold the pointer to a contour
    CvSeq* result;   //hold sequence of points of a contour
    CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

    cvFindContours(gray_img, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    //iterating through each contour
    while(contour) {
        //obtain a sequence of points of the countour, pointed by the variable 'countour'
        result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP,
                              cvContourPerimeter(contour) * 0.02, 0);

        //if there are 8 vertices
        if (result->total == 8) {
            //iterating through each point
            CvPoint *pt[8];
            for (int i = 0; i < 8; i++) {
                pt[i] = (CvPoint *) cvGetSeqElem(result, i);
            }

            //drawing lines around the triangle
            cvLine(img, *pt[0], *pt[1], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[1], *pt[2], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[2], *pt[3], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[3], *pt[4], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[4], *pt[5], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[5], *pt[6], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[6], *pt[7], cvScalar(255, 0, 0), 4);
            cvLine(img, *pt[7], *pt[0], cvScalar(255, 0, 0), 4);

        }


        //obtain the next contour
        contour = contour->h_next;
    }

    //show the image in which identified shapes are marked
    cvNamedWindow("Detected");
    cvShowImage("Detected",img);

    cvWaitKey(0); //wait for a key press

    //cleaning up
    cvDestroyAllWindows();
    cvReleaseMemStorage(&storage);
    cvReleaseImage(&img);
    cvReleaseImage(&gray_img);

    return 0;

}