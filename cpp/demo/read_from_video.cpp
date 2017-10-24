#include "opencv2/opencv.hpp"
#include "FrameDemo.h"
#include <math.h>

using namespace cv;

int readFromVideoFile(char* path)
{
	cv::String str(path);
	VideoCapture cap(str);

	if (!(cap.isOpened()))  // check if we succeeded
		return -1;

	const int FRAME_RATE = 24;
	const int FRAME_DELAY = floor(1000 / FRAME_RATE);

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera

		// check for empty frame (end of file)
		if (frame.empty())
			break;

		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(FRAME_DELAY) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}