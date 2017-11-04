#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "headers/FrameDemo.h"
#include <string>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	if (argc < 2) {
		cout << "Usage: framedemo [mode]" << endl;
		cout << "Where mode is:" << endl;
		cout << "\"img\": Open image" << endl;
		cout << "\"cam\": Read from camera" << endl;
		waitKey(0);
		return -1;
	}

	string img = "img";
	string cam = "cam";
	string vid = "vid";
	string cmd(argv[1]);

	if (cmd.compare(img) == 0) {
		if (argc < 3) {
			cout << " Usage: frameDemo ImageToLoadAndDisplay" << endl;
			return -1;
		}
		return openImage(argv[2]);
	} else if (cmd.compare(cam) == 0) {
		return readFromCamera();
	} else if (cmd.compare(vid) == 0) {
		if (argc < 3) {
			cout << " Usage: frameDemo VideoToLoadAndDisplay" << endl;
			return -1;
		}
		return readFromVideoFile(argv[2]);
	}
}

