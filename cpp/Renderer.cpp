#include "Renderer.h"
#include "NodeID.h"
#include "Frame.h"
#include "LogHelper.h"

#include "sd_render/Render.h"

void Renderer::setOutputMode(OutputMode mode)
{
    m_outputMode = mode;
}

void Renderer::run()
{
  FrameResult fr;
  // loop forever and wait for FrameResults to come in...
  namedWindow("Detected Signs", 1); // TODO only needed if visual
  for(;;){
    fr.receive(ANALYZER_A); // is this right?
    renderFrameResult(fr);
    
    //if(waitKey(30) >= 0)   // needed?
    //  break;
  }
}

void Renderer::renderFrameResult(FrameResult fr){
    // render frame based on output mode
  switch(m_outputMode){
  default: debugVisual(fr);
    // TODO other modes
  }
}

void debugVisual(FrameResult fr){
  std::vector<std::vector<cv::Point> > contours;
    contours = fr.region.contours; // TODO list of regions
        std::vector<cv::Point> approx;
        cv::Mat dst = fr.frameStruct.cFrame.clone();
        
        for (int i = 0; i < contours.size(); i++)
        {
            // Approximate contour with accuracy proportional
            // to the contour perimeter
            //cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
            
            // Skip small or non-convex objects
            //if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
	  //continue;

	    int shape = fr.region.shape;

	    sd_labelShape(dst, shape, contours[i]); // place label
        }

	// drawing contours
	for( int i = 0; i< contours.size(); i++ ) {
	  sd_drawContours(dst, contours);
	}

	// render visual output
        cv::imshow("Detected Signs", dst);
}
