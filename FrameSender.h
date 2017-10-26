#ifndef __FRAME_SENDER_H_
#define __FRAME_SENDER_H_

#include "opencv2/opencv.hpp"
#include <memory>

// MPI Node Identifiers
static const int MASTER_ID = 0;
static const int PREPROCESSOR_A = 1;
static const int PREPROCESSOR_B = 2;

// Frame structure
struct frame {
    cv::Mat frame;
    int index;
};


// Sends a frame structure from one node to another
void sendFrame(frame *framePtr, int receiver);

// Receives a frame structure sent by a node
std::unique_ptr<frame> receiveFrame();

// Extracts and sends frames from the given file (master node function)
void extractFrames(cv::String file);

#endif //__FRAME_SENDER_H_
