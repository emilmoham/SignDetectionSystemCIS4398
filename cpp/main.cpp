//
//  main.cpp
//  MPICH / OpenCV Test
//  Timothy Vaccarelli, 10/26/17
//
//  Michael Donahue, 10/25/17.
//

#include "mpi.h"
#include "ConfigParser.h"
#include "Frame.h"
#include "FrameResult.h"
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
    cv::Mat red1, red2, redFinal, yellowFinal;      //Color masks
    std::vector< std::vector<cv::Point> > contours; //Holds found contours
    std::vector<cv::Point> approx;                  //Used to find contours
    std::vector<cv::Vec4i> hierarchy;               //Used to draw contours
    int largestArea=0;
    int largestContourIndex=0;

    if (!receivedFrame) {
        LOG_ERROR("sd_renderer", "transferFrame(..) - Received null pointer for frame structure. Aborting");
        return;
    }

    /*Red Filter*/
    inRange(receivedFrame->cvFrame, Scalar(0, 80, 80), Scalar(10, 255, 255), red1);    //Low end of red mask
    inRange(receivedFrame->cvFrame, Scalar(170, 80, 80), Scalar(180, 255, 255), red2); //High end of red mask
    redFinal = red1 | red2; //Final Mat for red mask

    /*Yellow Filter*/
    inRange(receivedFrame->cvFrame, Scalar(25, 150, 150), Scalar(30, 255, 255), yellowFinal); //Yellow mask

    /*Edge pre-processing*/
    GaussianBlur(redFinal, redFinal, Size(9,9), 1.5, 1.5);                    //Blur red mask
    threshold (redFinal, redFinal, 0, 255, THRESH_BINARY|THRESH_OTSU);        //Threshold red mask
    GaussianBlur(yellowFinal, yellowFinal, Size(9,9), 1.5, 1.5);              //Blur yellow mask
    threshold (yellowFinal, yellowFinal, 0, 255, THRESH_BINARY|THRESH_OTSU);  //Threshold yellow mask

    /*Find and Draw contours in red mask*/
    findContours(redFinal, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);   //Find contours in red mask

    /*Iterate through contours and draw edges around positively detected regions*/
    for( int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

        if(fabs(contourArea(contours[i])) < 300 || !isContourConvex(approx)){   //Skip small stuff
            continue;
        }

        /*If a red sign with between 3 and 10 contours found (stop sign or yield). Contours are not always exact, thus the padding*/
        if (approx.size() > 3 && approx.size() < 10){
            double a = contourArea( contours[i], false);  //Find the area of contour

            /*Check if contour is the largest found within the color masked frame. If so, it's probably a sign.*/
            if(a > largestArea){
                largestArea = a;
                if (largestArea > 60){
                    largestContourIndex = i;
                    drawContours(receivedFrame->cvFrame, contours, largestContourIndex, color, 2, 8, hierarchy, 0, Point() );
                    largestArea = 0;
                }
            }
        }
    } //End contour loop

    /*Find and draw contours in yellow mask*/
    findContours(yellowFinal, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);
    largestArea = 0;

    /*Iterate through contours and draw edges around positively detected regions*/
    for( int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

        if(fabs(contourArea(contours[i])) < 300 || !isContourConvex(approx)){   //Skip small stuff
            continue;
        }

        /*If yellow sign between 2 and 5 contours found (warning sign). Contours are not always exact, thus the padding.*/
        if (approx.size() > 2 && approx.size() < 5){
            double a = contourArea(contours[i],false);  //Find the area of contour

            /*Check if contour is the largest found within the color masked frame. If so, it's probably a sign.*/
            if(a > largestArea){
                largestArea = a;
                if (largestArea > 60){
                    largestContourIndex = i;
                    drawContours(receivedFrame->cvFrame, contours, largestContourIndex, color, 2, 8, hierarchy, 0, Point() );
                    largestArea = 0;
                }
            }
        }
    } //End contour loop

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
        std::string videoFile = "roadsigns.MOV";
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
	  /*} else if (myId == RENDERER_ID) {
      Renderer rend;
      rend.setOutputMode(OutputMode::Debug);
      rend.run();*/
    }

    t1.join();
    MPI_Finalize();
    return 0;
}
