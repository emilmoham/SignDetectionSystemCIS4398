#ifndef __MASTER_H_
#define __MASTER_H_

#include "opencv2/opencv.hpp"
#include "Node.h"

/**
 * @class Master
 * @brief The master node of the cluster
 */
class Master : public Node
{
public:
    /// Default constructor
    Master() = default;

    /// Sets the video file to be used for frame parsing
    void setVideoFile(cv::String file);

    /// Runs the master node path of execution
    void run() override;

private:
    /// Extracts frames from the video source, sending them to the preprocessors
    void extractFrames();

private:
    /// File name for video capture
    cv::String m_videoFile;

    /// Frame counter
    int m_counter;
};

#endif //__MASTER_H_
