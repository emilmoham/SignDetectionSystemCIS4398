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
RNG rng(12345);

// Spawns a window and displays the frame
char transferFrame(Frame *receivedFrame)
{
    cv::Mat converted, red1, red2, redFinal, yellowFinal;      //Color masks
    std::vector< std::vector<cv::Point> > contours; //Holds found contours
    std::vector< std::vector<cv::Point> > contours2; //Holds found contours
    std::vector<cv::Point> approx;                  //Used to find contours
    std::vector<cv::Vec4i> hierarchy;               //Used to draw contours
    int largestArea=0;
    int largestContourIndex=0;

    if (!receivedFrame) {
        LOG_ERROR("sd_renderer", "transferFrame(..) - Received null pointer for frame structure. Aborting");
        return 27;
    }

    converted = receivedFrame->cvFrame.clone();

    LOG_DEBUG("profiler", "Starting red filter");
    /*Red Filter*/
    cvtColor(converted, converted, COLOR_BGR2HSV);
    inRange(converted, Scalar(0, 80, 80), Scalar(10, 255, 255), red1);    //Low end of red mask
    inRange(converted, Scalar(170, 80, 80), Scalar(180, 255, 255), red2); //High end of red mask
    redFinal = red1 | red2; //Final Mat for red mask
    LOG_DEBUG("profiler", "Finished red filter");

    LOG_DEBUG("profiler", "Starting yellow filter");
    /*Yellow Filter*/
    inRange(converted, Scalar(25, 150, 150), Scalar(30, 255, 255), yellowFinal); //Yellow mask
    LOG_DEBUG("profiler", "Finished yellow filter");

    LOG_DEBUG("profiler", "Starting red blur");
    /*Edge pre-processing*/
    GaussianBlur(redFinal, redFinal, Size(9,9), 1.5, 1.5);                    //Blur red mask
    threshold (redFinal, redFinal, 0, 255, THRESH_BINARY|THRESH_OTSU);        //Threshold red mask
    LOG_DEBUG("profiler", "Finished red blur");
    LOG_DEBUG("profiler", "Starting yellow blur");
    GaussianBlur(yellowFinal, yellowFinal, Size(9,9), 1.5, 1.5);              //Blur yellow mask
    threshold (yellowFinal, yellowFinal, 0, 255, THRESH_BINARY|THRESH_OTSU);  //Threshold yellow mask
    LOG_DEBUG("profiler", "Finished yellow blur");

    LOG_DEBUG("profiler", "Finding red contours");
    /*Find and Draw contours in red mask*/
    findContours(redFinal, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);   //Find contours in red mask
    LOG_DEBUG("profiler", "Found red contours");

    std::vector<vector<cv::Point> > contours_poly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    LOG_DEBUG("profiler", "Start drawing red contours");
    /*Iterate through contours and draw edges around positively detected regions*/
    for( int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar( 124, 252, 0 );
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
	approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
	boundRect[i] = boundingRect( Mat(contours_poly[i]) );

        if(fabs(contourArea(contours[i])) < 300 || !isContourConvex(approx)){   //Skip small stuff
            continue;
        }

        /*If a red sign with between 3 and 10 contours found (stop sign or yield). Contours are not always exact, thus the padding*/
        else if (approx.size() >= 3 && approx.size() < 7){
            double a = contourArea( contours[i], false);  //Find the area of contour

            /*Check if contour is the largest found within the color masked frame. If so, it's probably a sign.*/
            if(a > largestArea){
                largestArea = a;
                if (largestArea > 60){
                    largestContourIndex = i;
                    //drawContours(receivedFrame->cvFrame, contours, largestContourIndex, color, 2, 8, hierarchy, 0, Point() );
		    rectangle( receivedFrame->cvFrame, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		    putText(receivedFrame->cvFrame, "YIELD", cvPoint(30,30),
                                FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,0), 1, CV_AA);
                    largestArea = 0;
                }
            }
        }
	else if (approx.size() > 7 && approx.size() < 10){    //This line checks number of sides detected
                double a=contourArea( contours[i],false);  //  Find the area of cont
                if(a>largestArea){
                    largestArea=a;
                    if (largestArea > 60){
                        largestContourIndex=i;
                        //drawContours( receivedFrame->cvFrame, contours, largestContourIndex, color, 2, 8, hierarchy, 0, Point() );
                        rectangle( receivedFrame->cvFrame, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );                        
                        putText(receivedFrame->cvFrame, "STOP", cvPoint(30,30),
                                FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,0), 1, CV_AA);
                        largestArea = 0;
                    }
                }
            }
    } //End contour loop
    LOG_DEBUG("profiler", "Done drawing red contours");

    /*Find and draw contours in yellow mask*/
    LOG_DEBUG("profiler", "Finding yellow contours");
    findContours(yellowFinal, contours2, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);
    LOG_DEBUG("profiler", "Found yellow contours");
    largestArea = 0;

    LOG_DEBUG("profiler", "Drawing yellow contours");
    vector<Point> approx2;   //Vector of points for finding contours
    vector<vector<Point> > contours_poly2( contours2.size() );
    vector<Rect> boundRect2( contours2.size() );

    /*Iterate through contours and draw edges around positively detected regions*/
    for( int i = 0; i < contours2.size(); i++)
    {
	    Scalar color = Scalar( 124, 252, 0 );
            approxPolyDP(Mat(contours2[i]), approx2, arcLength(Mat(contours2[i]), true) * 0.02, true);
            approxPolyDP( Mat(contours2[i]), contours_poly2[i], 3, true );
            boundRect2[i] = boundingRect( Mat(contours_poly2[i]) );
            
            
            if(fabs(contourArea(contours2[i])) < 300 || !isContourConvex(approx2)){   //Skip small stuff
                continue;
            }
            
            else if (approx2.size() > 2 && approx2.size() < 6){    //This line checks number of sides detected
                double a=contourArea(contours2[i],false);  //  Find the area of cont
                if(a>largestArea){
                    largestArea=a;
                    if (largestArea > 50){
                        largestContourIndex=i;
                        //cout << largest_area;
                        //drawContours( receivedFrame->cvFrame, contours2, largestContourIndex, color, 2, 8, hierarchy, 0, Point() );
                        rectangle( receivedFrame->cvFrame, boundRect2[i].tl(), boundRect2[i].br(), color, 2, 8, 0 );
                        putText(receivedFrame->cvFrame, "WARNING", cvPoint(30,30),
                                FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,0), 1, CV_AA);
                        largestArea = 0;
                    }
                }   
            }
    } //End contour loop
    LOG_DEBUG("profiler", "Done drawing yellow contours");

    // Simple display of each frame
    imshow("MPI Stream", receivedFrame->cvFrame);
    return (char)waitKey(40);
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
	// get fps, width, height of video
	int buffer[3];
	MPI_Recv(&buffer[0], 3, MPI_INT, MASTER_ID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

        FrameResult frameRes;
        int counter = 0;
        namedWindow("MPI Stream",1);
	VideoWriter writer;
	writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), buffer[0], Size(buffer[1], buffer[2]), true); 
	if (!writer.isOpened())
		LOG_ERROR("output", "Could not open output file");
	char c = '\0';
	int i = 0;
        while (c != 27)
        {
            frameRes.receive((counter % 2 == 0) ? ANALYZER_A : ANALYZER_B);
	    counter++;
            c = transferFrame(&frameRes.frame);
	    writer.write(frameRes.frame.cvFrame);
            //TODO: Rendering code not implemented. Must convert regions data in FrameResult into visible region in the
            //      original frame (frameRes.frame), or modify frameRes.frame to include bounding boxes, text, etc before calling transferFrame
        }
	writer.release();
    }

    t1.join();
    MPI_Finalize();
    return 0;
}
