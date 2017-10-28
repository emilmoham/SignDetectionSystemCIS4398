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

// Spawns a window and displays the frame
void transferFrame(Frame *receivedFrame)
{
    if (!receivedFrame) {
        std::cout << "transferFrame(..) - Received null pointer for Frame struct. Aborting." << std::endl;
        return;
    }
    // Simple display of the frame
    namedWindow("MPI Image",1);
    imshow("MPI Image", receivedFrame->cvFrame);
    waitKey(0);
}

int main(int argc, char** argv)
{
    int myId, numNodes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);
    if (myId == MASTER_ID) {
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

