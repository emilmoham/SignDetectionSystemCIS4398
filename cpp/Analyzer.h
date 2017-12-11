#ifndef __ANALYZER_H_
#define __ANALYZER_H_
                                                                                                                                                                                               
#include <opencv2/opencv.hpp>
#include "FrameResult.h"
#include "Node.h"
#include "Region.h"
#include "TextExtractor.h"
#include <vector>

/// Color masks the analyzer can use
enum class ColorMask
{
    None = 0,
    Red,
    Yellow,
    White
};

/**
 * @class Analyzer
 * @brief Handles the more detailed classification process of the flagged regions in a frame, setting the 
 *        signType and (optionally) signText members of each \ref Region belonging to the \ref FrameResult 
 *        objects before passing the data on to a rendering node 
 */
class Analyzer : public Node
{
public:
    /// Default constructor
    Analyzer() = default;

    /// Specifies which color mask the analyzer should use on frames
    void setColorMask(ColorMask mask);

    /// Runs the analyzer's main execution loop - retrieving preprocessed frame data and 
    /// running a classification process in order to extract sign information before sending
    /// the results to a rendering node
    void run() override;

private:
    /// Searches the specified regions of the current frame for indicators as to the type of sign (if any)
    /// in each region, as well as any text or other useful information
    void getSignInformation(FrameResult &frameResult);

private:
    /// Width of frames
    int m_width;

    /// Height of frames
    int m_height;

    /// Text extractor module
    TextExtractor m_textExtractor;

    /// Used to find contours during analysis
    std::vector<cv::Point> m_approx;

    /// Regions, used in each call to getSignInformation()
    Region m_region, m_regionPoly;

    /// Color mask used by the node
    ColorMask m_colorMask;
};

#endif //__ANALYZER_H_

