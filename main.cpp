//
//  main.cpp
//  OpenCV Test
//
//  Created by Michael Donahue on 10/25/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

/*Frame struct*/
struct frame{
    Mat frame;
    int index;
};

//Receives a frame and displays
void transferFrame(frame *receivedFrame){
    
    Mat edges;
    namedWindow("edges",1);
    
    Mat localFrame = receivedFrame->frame;	//Frame passed in
    int localIndex = receivedFrame->index;	//Index passed in
    
    
    std::cout << localIndex;	//Output index to make sure its accurate
    
    cvtColor(localFrame, edges, COLOR_BGR2GRAY);
    GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    Canny(edges, edges, 0, 30, 3);
    imshow("edges", edges);	//Show frame passed in
}

int main(int, char**)
{
    
    cv::String file("test2.mp4");
    
    VideoCapture cap(file); // open the default camera
    if(!cap.isOpened()){  // check if we succeeded
        std::cout << "Failed";	//Print if we failed
        return -1;
    }

    int counter = 0;	//Used as index for the frame struct
    for(;;)
    {
        frame frameStruct;	//Make a new frame struct
        Mat frameFromVideo;	
        cap >> frameFromVideo; // get a new frame from camera
        
        frameStruct.frame = frameFromVideo;	//Set struct Mat object to current frame
        frameStruct.index = counter;	//Set struct index to current count
        counter++;			//Increment count
        
        transferFrame(&frameStruct);	//Send to function for processing
        if(waitKey(30) >= 0)		//This goes here to work
            break;

    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

