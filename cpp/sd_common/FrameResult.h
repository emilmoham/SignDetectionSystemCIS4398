#ifndef __FRAMERESULT_H_
#define __FRAMERESULT_H__

#include "opencv2/opencv.hpp"
#include "Passable.h"
#include "Frame.h"
#include "Region.h"

/**
 * @class FrameResult
 * Structure of preprocessed/analyzed Frame
 */
class FrameResult : public Passable
{
public:
    // Frame struct
    Frame frameStruct;
    
    // Regions
    Region region; // TODO convert to some List<Region>

    // FrameResult constructor
    FrameResult();

    // Constructs a FrameResult, given the Frame struct and Region
    FrameResult(Frame frameStruct, Region region); // TODO list of Region
    
    // Frame destructor - frees memory allocated to m_buffer if it was used during the lifetime of the frame
    ~FrameResult();

    virtual void send(int recipient) override;

    // Receives the FrameResult from a sender, populating the data fields of the caller
    virtual void receive(int sender) override;

private:
    /// Buffer for raw frame data - when passing frame through MPI and converted into a cv::Mat,
    /// the Mat object points to the buffer and it is up to the Frame object to deallocate the buffer
    unsigned char *m_buffer; // TODO might need a buffer for members?

    /// Stores the size of the buffer
    size_t m_bufferLen; // TODO "
};

#endif //__FRAMERESULT_H_

