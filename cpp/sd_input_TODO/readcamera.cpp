#include "opencv2/opencv.hpp"
#include "Input.h"
#include <iostream>

using namespace cv;
using namespace std;

int ripFrames(InputMode mode, char* path) {
	if (mode == Camera)
		return readFromCamera();
	else { // mode is VideoFile
		if (String(path).empty()) {
			cout << "In video input mode, you must specify the path." << endl;
		}

		return readFromVideoFile(path);
	}
}

int readFromCamera()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

