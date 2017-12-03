//
//  main.cpp
//  MPICH / OpenCV Test
//  Timothy Vaccarelli, 10/26/17
//
//  Created by Michael Donahue on 10/25/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//

#include "mpi.h"
#include "ConfigParser.h"
#include "Frame.h"
#include "NodeID.h"
#include "Master.h"
#include "Preprocessor.h"
#include "Analyzer.h"
#include "LogHelper.h"
#include "SysInfo.h"
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace cv;

LogHelper sLog;

// Spawns a window and displays the frame
void transferFrame(Frame *receivedFrame)
{
    if (!receivedFrame) {
        LOG_ERROR("sd_renderer", "transferFrame(..) - Received null pointer for frame structure. Aborting");
        return;
    }

    // Simple display of each frame
    imshow("MPI Stream", receivedFrame->cvFrame);
    waitKey(40);
}

int main(int argc, char** argv)
{
    int myId, numNodes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);

    // Attempt to load from the configuration file, using default settings on failure
    ConfigParser cfg;
    bool cfgLoaded = cfg.load("Config.ini");
    if (cfgLoaded)
    {
        sLog.setLogDir(cfg.getValue<std::string>("LogDir"));
        int logLevel = cfg.getValue<int>("LogLevel");
        sLog.get("serializable")->SetLogLevel(logLevel);
        sLog.get("sd_node.Master")->SetLogLevel(logLevel);
        sLog.get("sd_renderer")->SetLogLevel(logLevel);
        sLog.get("sd_textextraction")->SetLogLevel(logLevel);
        sLog.get("SysInfo")->SetLogLevel(logLevel);
    }
    else
    {
        sLog.setLogDir("./");
    }
    
    // Initialize info / debugging class and run in separate thread before main node objects are initialized
    SysInfo info(myId);
    std::thread t1(&SysInfo::run, &info);

    if (myId == MASTER_ID) {
        Master master;

        // Attempt to load settings from config file, defaulting to test2.mp4 if config not loaded
        InputType mode = InputType::File;
        std::string videoFile = "test2.mp4";
        if (cfgLoaded)
        {
            mode = static_cast<InputType>(cfg.getValue<int>("InputType"));
            videoFile = cfg.getValue<std::string>("InputFile");
        }
        master.setInputType(mode);
        master.setVideoFile(cv::String(videoFile));
        master.run();
    } else if (myId == PREPROCESSOR_ID) {
        Preprocessor preproc;
        preproc.run();
/*
        namedWindow("MPI Stream",1);
	    for (;;)
	    {
            f.receive(MASTER_ID);
            transferFrame(&f);
	    }
*/
    } else if (myId == ANALYZER_A || myId == ANALYZER_B) {
        Analyzer analyzer;
        analyzer.run();
    } else if (myId == RENDERER_ID) {
        FrameResult frameRes;
        int counter = 0;
        namedWindow("MPI Stream",1);
        for (;;)
        {
            frameRes.receive((counter % 2 == 0) ? ANALYZER_A : ANALYZER_B);
            transferFrame(&frameRes.frame);
            //TODO: Rendering code not implemented. Must convert regions data in FrameResult into visible region in the 
            //      original frame (frameRes.frame), or modify frameRes.frame to include bounding boxes, text, etc before calling transferFrame
        }
    }

    t1.join();
    MPI_Finalize();
    return 0;
}

