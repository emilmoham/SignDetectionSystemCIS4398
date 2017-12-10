//
//  main.cpp
//  MPICH / OpenCV Test
//  Timothy Vaccarelli, 10/26/17
//
//  Michael Donahue, 10/25/17.
//

#include <mpi.h>
#include "ConfigParser.h"
#include "Frame.h"
#include "NodeID.h"
#include "Master.h"
#include "Analyzer.h"
#include "Renderer.h"
#include "LogHelper.h"
#include "SysInfo.h"
#include <cstdlib>
#include <iostream>
#include <thread>

LogHelper sLog;
RNG rng(12345);

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
	    sLog.get("profiler")->SetLogLevel(logLevel);
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
        std::string videoFile = "roadsigns.MOV";
        if (cfgLoaded)
        {
            mode = static_cast<InputType>(cfg.getValue<int>("InputType"));
            videoFile = cfg.getValue<std::string>("InputFile");
        }
        master.setInputType(mode);
        master.setVideoFile(cv::String(videoFile));
        master.run();
    } else if (myId == ANALYZER_A || myId == ANALYZER_B || myId == ANALYZER_C) {
        Analyzer analyzer;
        analyzer.run();
    } else if (myId == RENDERER_ID) {
        Renderer renderer;
        renderer.run();
    }

    t1.join();
    MPI_Finalize();
    return 0;
}
