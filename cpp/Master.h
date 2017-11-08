#ifndef __MASTER_H_
#define __MASTER_H_

#include "opencv2/opencv.hpp"
#include "Node.h"

/// Types of input from which the master node can extract data
enum class InputType
{
    File = 0,    // Video files
    Stream       // Reading from input stream, e.g. webcams
};

/**
 * @class Master
 * @brief The master node of the cluster
 */
class Master : public Node
{
public:
    /// Default constructor
    Master() = default;

    /// Sets the input type that the master will use for video processing
    void setInputType(InputType type);

    /// Sets the video file to be used for frame parsing
    void setVideoFile(cv::String file);

    /// Runs the master node path of execution
    void run() override;

private:
    /// Extracts frames from the video source, sending them to the preprocessors
    void extractFrames();

private:
    /// Input type
    InputType m_inputType;

    /// File name for video capture
    cv::String m_videoFile;

    /// Frame counter
    int m_counter;
};

#endif //__MASTER_H_
