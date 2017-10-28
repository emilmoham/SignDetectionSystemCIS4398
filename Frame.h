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

    // Frame constructor
    Frame();

    // Constructs a frame, given the OpenCV frame object and an index
    Frame(cv::Mat frame, int frameIndex);
    
    // Frame destructor - frees memory allocated to m_buffer if it was used during the lifetime of the frame
    ~Frame();

    // Sends the frame to the given recipient
    virtual void send(int recipient) override;

    // Receives the frame from a sender, populating the data fields of the caller
    virtual void receive(int sender) override;

private:
    /// Buffer for raw frame data - when passing frame through MPI and converted into a cv::Mat,
    /// the Mat object points to the buffer and it is up to the Frame object to deallocate the buffer
    unsigned char *m_buffer;
};

#endif //__FRAME_H_

