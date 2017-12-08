#include "NodeID.h"
#include "Preprocessor.h"
#include <utility>

void Preprocessor::run()
{
    int counter = 0;

    for (;;)
    {
        Frame f;
        f.receive(MASTER_ID);
        getFrameResult(std::move(f));

        frameResult.send((counter % 2 == 0) ? ANALYZER_A : ANALYZER_B);
        ++counter;
    }
}

void Preprocessor::getFrameResult(Frame &&f)
{
    frameResult = FrameResult(std::move(f));

    // Make opencv / sd module calls here to place each region into the regions member of frameResult
    // ex:
    //     vector <Region> regionsOfInterest = getAllRegions(frameResult.frame);
    //           -> where each Region stores a vector of cv::Points, a color value (currently an Enum, see cpp/sd_common/Colors.h),
    //              and a shape value (also an enum, see cpp/sd_common/Shapes.h)
    //     frameResult.regions = regionsOfInterest;
}

