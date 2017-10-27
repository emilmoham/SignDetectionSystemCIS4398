//
//  main.cpp
//  MPICH / OpenCV Test
//  Timothy Vaccarelli, 10/26/17
//
//  Created by Michael Donahue on 10/25/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//

#include "mpi.h"
#include "Frame.h"
#include "NodeID.h"
#include "Master.h"
#include <cstdlib>
#include <iostream>

using namespace cv;

//Receives a frame and displays
void transferFrame(Frame *receivedFrame){
    
    Mat edges;
    namedWindow("edges",1);
    
    Mat localFrame = receivedFrame->cvFrame;	//Frame passed in
    int localIndex = receivedFrame->index;	//Index passed in
    
    
    std::cout << localIndex;	//Output index to make sure its accurate
    
    cvtColor(localFrame, edges, COLOR_BGR2GRAY);
    GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    Canny(edges, edges, 0, 30, 3);
    imshow("edges", edges);	//Show frame passed in
}

int main(int argc, char** argv)
{
    int myId, numNodes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);
    if (myId == MASTER_ID) {
    	extractFrames(cv::String("test2.mp4"));
        Master master;
        master.setVideoFile(cv::String("test2.mp4"));
        master.run();
    } else if (myId == PREPROCESSOR_A || myId == PREPROCESSOR_B) {
        Frame f;
        f.receive(MASTER_ID);
        transferFrame(&f);
    }
    return 0;
}

