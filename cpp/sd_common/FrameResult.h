#ifndef __FRAME_RESULT_H_
#define __FRAME_RESULT_H_

#include "Frame.h"
#include "Passable.h"
#include "Region.h"
#include <utility>

/**
 * @class FrameResult
 * @brief Represents the results of analysis of a single frame
 */
class FrameResult : public Passable
{
public:
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
