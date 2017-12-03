#include <mpi.h> 
#include "Master.h"
#include "NodeID.h"
#include "Frame.h"
#include "LogHelper.h"

void Master::setInputType(InputType type)
{
    m_inputType = type;
}

void Master::setVideoFile(cv::String file)
{
    m_videoFile = file;
}

void Master::run()
{
    m_counter = 0;
    extractFrames();
}

void Master::extractFrames()
{
    // Open video source
    cv::VideoCapture cap; 
    bool ok = false;
    switch (m_inputType)
    {
        case InputType::File:
            ok = cap.open(m_videoFile);
            break;
        case InputType::Stream:
            ok = cap.open(0);
            break;
    }
    
    // Handle errors if any
    if (!ok)
    {
        LOG_ERROR("sd_node.Master", "Could not open video input");
        return;
    }

    // Determine FPS of video source
    //int fps = (int) cap.get(CV_CAP_PROP_FPS);
    //int delay = 1000 / fps;

    // Send delay information to rendering node
    // TODO: only send delay info to the rendering node. need to pick a specific node or broadcast to all nodes
    //MPI_Send(&delay, 1, MPI_INT, PREPROCESSOR_A, 0, MPI_COMM_WORLD);
    //LOG_DEBUG("sd_node.Master", "Sent suggested delay between frames of ", delay, " to node ", PREPROCESSOR_A);

    Frame frameStruct;
    for (;;)
    {
        // Extract the next frame from the video source
        cap >> frameStruct.cvFrame;

        // Assign an index to the frame
        frameStruct.index = m_counter;

        //frameStruct.send((m_counter % 2 == 0) ? PREPROCESSOR_A : PREPROCESSOR_B);
        frameStruct.send(PREPROCESSOR_ID);

        // Increment counter
        ++m_counter;
    }
}

