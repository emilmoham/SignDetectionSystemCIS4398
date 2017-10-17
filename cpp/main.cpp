#include "SignDetection.h"

using namespace std;
//using namespace cv;

int main(int argc, char **argv){
    queue<struct FrameResult> q;

    struct Frame frame_obj(10);
    struct Region region_obj(1, 2, 3, 4);
    struct FrameResult fr(frame_obj, region_obj);

    fr.print();

    return 0;
}
