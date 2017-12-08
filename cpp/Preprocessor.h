#ifndef __PREPROCESSOR_H_
#define __PREPROCESSOR_H_
                                                                                                                                                                                               
#include "opencv2/opencv.hpp"
#include "FrameResult.h"
#include "Node.h"

/**
 * @class Preprocessor
 * @brief Handles the initial screening of frames sent by the master node,
 *        to determine which regions potentially contain signs
 */
class Preprocessor : public Node
{
public:
    /// Default constructor
    Preprocessor() = default;

    /// Runs the preprocessor's main execution loop - retrieving frames and filtering regions
    /// for potential signs before passing the data to an analyzer node
    void run() override;

private:
    /// Searches the given frame for regions that might contain sign information, returning
    /// the result as a \ref FrameResult object
    void getFrameResult(Frame &&frame);

private:
    /// Stores the current frame result
    FrameResult frameResult;
};

#endif //__PREPROCESSOR_H_

