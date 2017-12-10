#include <mpi.h> 
#include "Master.h"
#include "NodeID.h"
#include "Frame.h"
#include "FrameResult.h"
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
    int buffer[3];
    buffer[0] = (int) cap.get(CV_CAP_PROP_FPS); // fps
    buffer[1] = (int) cap.get(CV_CAP_PROP_FRAME_WIDTH);
    buffer[2] = (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    MPI_Send(&buffer[0], 3, MPI_INT, RENDERER_ID, 0, MPI_COMM_WORLD);
 
    //Frame frameStruct;
    FrameResult fr;
    for (;;)
    {
        // Extract the next frame from the video source
        cap >> fr.frame.cvFrame;

        // Assign an index to the frame
        fr.frame.index = m_counter;

        //frameStruct.send(PREPROCESSOR_ID);
        fr.send(ANALYZER_A);
        fr.send(ANALYZER_B);
        fr.send(ANALYZER_C);
        fr.send(RENDERER_ID);

        // Increment counter
        ++m_counter;
    }
}

