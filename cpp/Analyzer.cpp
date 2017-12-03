#include "Analyzer.h"
#include "NodeID.h"

void Analyzer::run()
{
    FrameResult frameRes;
    for (;;)
    {
        frameRes.receive(PREPROCESSOR_ID);
        getSignInformation(frameRes);

        frameRes.send(RENDERER_ID);
    }
}

void Analyzer::getSignInformation(FrameResult &frameResult)
{
    // Make the calls to the opencv / sign detection modules here
    // for each region in the frame result vector, in order to determine
    // exactly what types of signs are found and also to extract other
    // info. such as text

    /* Example:
       for (Region &r : frameResult.regions)
       {
           r.signType = getSignType(frameResult.frame, r);

           cv::Mat signRegionMat = ... (convert the contour region from the frame into a cv::Mat structure)
           r.signText = m_textExtractor.getText(signRegionMat); 
       }
    */
}

