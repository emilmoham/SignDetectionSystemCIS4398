//
//  main.cpp
//  MPICH / OpenCV Test
//  Timothy Vaccarelli, 10/26/17
//
//  Created by Michael Donahue on 10/25/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//

#include "mpi.h"
#include "FrameSender.h"
#include <cstdlib>
#include <iostream>

using namespace cv;

const int MAX_BYTES = 8 * 1024 * 1024;
unsigned char buffer[MAX_BYTES];

void sendFrame(frame *framePtr, int receiver)
{
    Mat cvFrame = framePtr->frame;
    int rows = cvFrame.rows;
    int cols = cvFrame.cols;
    int type = cvFrame.type();
    int channels = cvFrame.channels();

    // Copy frame metadata into buffer
    memcpy(&buffer[0 * sizeof(int)], (unsigned char*)&rows, sizeof(int));
    memcpy(&buffer[1 * sizeof(int)], (unsigned char*)&cols, sizeof(int));
    memcpy(&buffer[2 * sizeof(int)], (unsigned char*)&type, sizeof(int));

    int bytesPerSample = 1;
    int numBytes = rows * cols * channels * bytesPerSample;

    if (!cvFrame.isContinuous())
        cvFrame = cvFrame.clone();

    // Copy frame data into buffer 
    memcpy(&buffer[3 * sizeof(int)], cvFrame.data, numBytes);

    // Send frame index followed by frame data to the receiver
    MPI_Send(&(framePtr->index), 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
    MPI_Send(&buffer, numBytes + 3 * sizeof(int), MPI_UNSIGNED_CHAR, receiver, 0, MPI_COMM_WORLD);
}

std::unique_ptr<frame> receiveFrame()
{
    std::unique_ptr<frame> frameStruct(new frame);

    MPI_Status status;
    int rows, cols, type, channels, count;

    MPI_Recv(&frameStruct->index, sizeof(int), MPI_INT, MASTER_ID, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&buffer, sizeof(buffer), MPI_UNSIGNED_CHAR, MASTER_ID, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_UNSIGNED_CHAR, &count);
    memcpy((unsigned char*)&rows, &buffer[0 * sizeof(int)], sizeof(int));
    memcpy((unsigned char*)&cols, &buffer[1 * sizeof(int)], sizeof(int));
    memcpy((unsigned char*)&type, &buffer[2 * sizeof(int)], sizeof(int));

    // Create the CV Mat based on data sent by the master
    frameStruct->frame = Mat(rows, cols, type, (unsigned char*)&buffer[3*sizeof(int)]);
    
    return std::move(frameStruct);
}


// Extracts frames from a video file and sends them to a node
void extractFrames(cv::String file) {
    // Open default camera
    VideoCapture cap(file);

    // Handle errors if any
    if (!cap.isOpened()) {
        std::cout << "Failed to open video file" << std::endl;
        return;
    }

    // Stores index of current frame
    int counter = 0;
    for (;;) {
        // Extract the next frame from the video source
        frame frameStruct;
        Mat frameFromVideo;
        cap >> frameFromVideo;

        // Store frame into our frame structure
        frameStruct.frame = frameFromVideo;
        frameStruct.index = counter;

        // Send to a preprocessor
        sendFrame(&frameStruct, (counter % 2 == 0) ? PREPROCESSOR_A : PREPROCESSOR_B);

        // Increment counter
        ++counter;

        if (waitKey(30) >= 0)
            break;
    }
}

