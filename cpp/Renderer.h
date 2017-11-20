#ifndef __RENDERER_H_
#define __RENDERER_H_

#include "opencv2/opencv.hpp"
#include "Node.h"
#include "headers/FrameStructs.h"

/// Modes of output 
enum class OutputMode
{
    Debug = 0,       // Contours, bounding boxes, labels, etc.
    SimpleVisual,    // Labels
    DetailedVisual,  // Labels & contours
    Audio,           // Just audio
    AudioAndVisual   // Audio and visual output
};

/**
 * @class Renderer
 * @brief The node responsible for rendering visual/audio output from the cluster
 */
class Renderer : public Node
{
public:
    /// Default constructor
    Renderer() = default;

    /// Sets the output mode
    void setOutputMode(OutputMode mode);

    /// Sets the video file to be used for frame parsing
    //void setVideoFile(cv::String file);

    void renderFrameResult(FrameResult fr);

    /// Runs the renderer node path of execution
    void run() override;

private:
    /// Extracts frames from the video source, sending them to the preprocessors
    //void extractFrames();

private:
    /// Input type
    OutputMode m_outputMode;

    /// File name for video capture
    //cv::String m_videoFile;

    /// Frame counter
    //int m_counter;

    /// 
};

#endif //__RENDERER_H_
