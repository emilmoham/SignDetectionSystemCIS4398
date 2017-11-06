//
//  main.cpp
//  ShapeDetection
//
//  Created by Michael Donahue on 11/3/17.
//  Copyright © 2017 Michael Donahue. All rights reserved.
//

#include "../headers/OpenCVHeaders.h"
#include "Contour.h"
#include "../sd_render/Render.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image = imread("road-signs.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    vector<vector<Point> > contours;
    contours = sd_getcontours(image);
    Mat output = sd_drawcontours(image, contours);
    
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", output ); // Show our image inside it.
    
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
