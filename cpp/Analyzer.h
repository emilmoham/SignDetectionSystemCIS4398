#ifndef __ANALYZER_H_
#define __ANALYZER_H_
                                                                                                                                                                                               
#include "opencv2/opencv.hpp"
#include "FrameResult.h"
#include "Node.h"
#include "TextExtractor.h"

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

    /// Runs the analyzer's main execution loop - retrieving preprocessed frame data and 
    /// running a classification process in order to extract sign information before sending
    /// the results to a rendering node
    void run() override;

private:
    /// Searches the specified regions of the current frame for indicators as to the type of sign (if any)
    /// in each region, as well as any text or other useful information
    void getSignInformation(FrameResult &frameResult);

private:
    /// Text extractor module
    TextExtractor m_textExtractor;
};

#endif //__ANALYZER_H_

