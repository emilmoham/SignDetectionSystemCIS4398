#ifndef __RENDERER_H_
#define __RENDERER_H_

#include "opencv2/opencv.hpp"
#include "Node.h"
#include "FrameResult.h"

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

    /// Overlays sign information on top of the given frame before rendering it to the screen
    void renderFrameResult(FrameResult &fr);

    /// Runs the renderer node path of execution
    void run() override;

private:
    /// Extracts frames from the video source, sending them to the preprocessors
    //void extractFrames();

private:
    /// Input type
    OutputMode m_outputMode;
};

#endif //__RENDERER_H_
