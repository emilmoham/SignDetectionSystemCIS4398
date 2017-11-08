#include "Master.h"
#include "NodeID.h"
#include "Frame.h"
#include <iostream>

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
        std::cout << "[Master Node]: Fatal error - could not open video input" << std::endl;
        return;
    }

    Frame frameStruct;
    for (;;)
    {
        // Extract the next frame from the video source
        cap >> frameStruct.cvFrame;

        // Assign an index to the frame
        frameStruct.index = m_counter;

        //frameStruct.send((m_counter % 2 == 0) ? PREPROCESSOR_A : PREPROCESSOR_B);
	frameStruct.send(PREPROCESSOR_A);

        // Increment counter
        ++m_counter;
    }
}

