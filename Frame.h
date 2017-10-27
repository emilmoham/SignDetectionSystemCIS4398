#ifndef __FRAME_H_
#define __FRAME_H__

#include "opencv2/opencv.hpp"
#include "Passable.h"

/**
 * @class Frame
 * Structure of an individual frame
 */
class Frame : public Passable
{
public:
    // OpenCV frame
    cv::Mat cvFrame;

    // Index of the frame, relative to its position in the video stream
    int index;

    // Default constructor
    Frame() = default;

    // Constructs a frame, given the OpenCV frame object and an index
    Frame(cv::Mat frame, int frameIndex);

    // Sends the frame to the given recipient
    virtual void send(int recipient) override;

    // Receives the frame from a sender, populating the data fields of the caller
    virtual void receive(int sender) override;
};

#endif //__FRAME_H_

