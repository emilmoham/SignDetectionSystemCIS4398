#include "Master.h"
#include "NodeID.h"
#include "Frame.h"
#include <iostream>

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
    VideoCapture cap(m_videoFile);

    // Handle errors if any
    if (!cap.isOpened())
    {
        std::cout << "Failed to open video file." << std::endl;
        return;
    }

    for (;;)
    {
        // Extract the next frame from the video source
        Frame frameStruct;
        cap >> frameStruct.cvFrame;

        // Assign an index to the frame
        frameStruct.index = counter;

        frameStruct.send((counter % 2 == 0) ? PREPROCESSOR_A : PREPROCESSOR_B);

        // Increment counter
        ++counter;
    }
}
