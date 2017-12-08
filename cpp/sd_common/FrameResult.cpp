#include <mpi.h>
#include "LogHelper.h"
#include "FrameResult.h"
#include <utility>

FrameResult::FrameResult(const FrameResult &other)
{
    frame = other.frame;
    regions = other.regions;
}

FrameResult::FrameResult(FrameResult &&other)
{
    frame = std::move(other.frame);
    regions = std::move(other.regions);
}

FrameResult::FrameResult(Frame &&f) :
    frame(std::move(f)),
    regions()
{
}

void FrameResult::send(int recipient)
{
    LOG_DEBUG("serializable", "FrameResult::send(..) called. Sending frame (index ", frame.index, ") to node ", recipient);

    frame.send(recipient);

    int numRegions = static_cast<int>(regions.size());
    MPI_Send(&numRegions, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    for (Region &r : regions)
        r.send(recipient);
}

void FrameResult::receive(int sender)
{
    regions.clear();

    frame.receive(sender);

    int numRegions = 0;
    MPI_Recv(&numRegions, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for (int i = 0; i < numRegions; ++i)
    {
        Region r;
        r.receive(sender);
        regions.push_back(r);
    }

    LOG_DEBUG("serializable", "FrameResult::receive(..) called. Got frame (index ", frame.index, ") from node ", sender);
}

