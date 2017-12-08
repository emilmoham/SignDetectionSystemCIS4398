#ifndef __FRAME_H_
#define __FRAME_H_

#include "opencv2/opencv.hpp"
#include "Passable.h"
#include <utility>

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

    // Copy constructor
    Frame(const Frame &other);

    // Move constructor
    Frame(Frame &&other);

    // Copy assignment operator
    Frame &operator=(const Frame &other)
    {
        cvFrame = other.cvFrame;
	index = other.index;
	m_buffer = other.m_buffer;
	m_bufferLen = other.m_bufferLen;
    }

    // Move assignment operator
    Frame &operator=(Frame &&other)
    {
        cvFrame = other.cvFrame;
        index = other.index;
        m_buffer = other.m_buffer;
        m_bufferLen = other.m_bufferLen;

        other.m_buffer = nullptr;
        other.m_bufferLen = 0;

        return *this;
    }
    
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

    /// Stores the size of the buffer
    size_t m_bufferLen;
};

#endif //__FRAME_H_

