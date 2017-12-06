<<<<<<< HEAD
#ifndef __FRAME_RESULT_H_
#define __FRAME_RESULT_H_

#include "Frame.h"
#include "Passable.h"
#include "Region.h"
#include <utility>

/**
 * @class FrameResult
 * @brief Represents the results of analysis of a single frame
=======
#ifndef __FRAMERESULT_H_
#define __FRAMERESULT_H__

#include "opencv2/opencv.hpp"
#include "Passable.h"
#include "Frame.h"
#include "Region.h"

/**
 * @class FrameResult
 * Structure of preprocessed/analyzed Frame
>>>>>>> renderer
 */
class FrameResult : public Passable
{
public:
<<<<<<< HEAD
    /// Default constructor
    FrameResult() = default;

    /// FrameResult constructor
    FrameResult(Frame &&f);

    /// Assignment operator
    FrameResult &operator=(const FrameResult &other)
    {
        frame.cvFrame = other.frame.cvFrame;
        frame.index = other.frame.index;
        regions = other.regions;
        return *this;
    }

    /// Assignment move operator
    FrameResult& operator=(FrameResult &&other)
    {
        frame = std::move(other.frame);
        regions = std::move(other.regions);
        return *this;
    }

    /// Sends the frame result to the node with the given MPI identifier
    virtual void send(int recipient) override;

    /// Receives the frame result from the node with the given MPI identifier
    virtual void receive(int sender) override;

public:
    /// The frame
    Frame frame;

    /// A collection of regions containing sign information
    std::vector<Region> regions;
};

#endif //__FRAME_RESULT_H_
=======
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

>>>>>>> renderer
