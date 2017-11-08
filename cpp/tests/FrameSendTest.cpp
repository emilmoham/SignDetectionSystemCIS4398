#include "mpi.h"
#include "Frame.h"
#include "NodeID.h"
#include <cstdlib>
#include "SHA256.h"

using namespace cv;

void sendFrameWithDigest(const cv::String &file) {
    // Open default camera
    VideoCapture cap(file);

    // Handle errors if any
    if (!cap.isOpened()) {
        std::cout << "Failed to open video file" << std::endl;
        return;
    }

    cap.set(1, 150);

    // Extract and send the first frame, along with its SHA256 digest
    Frame frameStruct;
    cap >> frameStruct.cvFrame;

    // Send digest
    const Mat &f = frameStruct.cvFrame;
    uint32_t *frameDigest = SHA256Hash((uint8_t*)f.data, f.rows * f.cols * f.channels());
    MPI_Send(&frameDigest[0], SHA256_ARRAY_LEN, MPI_UNSIGNED, PREPROCESSOR_A, 0, MPI_COMM_WORLD);
    free(frameDigest);
    frameStruct.send(PREPROCESSOR_A);
}

// Reads a frame structure from the master node, verifying its integrity by comparing the
// given digest value of the frame to the calculated value after receiving the frame data
void receiveAndVerifyFrame() {
    // First read the digest value
    uint32_t digestGiven[SHA256_ARRAY_LEN];
    MPI_Recv(&digestGiven[0], SHA256_ARRAY_LEN, MPI_UNSIGNED, MASTER_ID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Received hash value of frame" << std::endl;

    Frame frameStruct;
    frameStruct.receive(MASTER_ID);
    std::cout << "Received frame structure" << std::endl;

    // Calculate the frame's digest
    const Mat &f = frameStruct.cvFrame;
    uint32_t *digestCalc = SHA256Hash((uint8_t*)f.data, f.rows * f.cols * f.channels());

    // Compare digest values
    for (int i = 0; i < SHA256_ARRAY_LEN; ++i) {
        if (digestGiven[i] != digestCalc[i]) {
	    std::cout << "[Test] [Preprocessor A]: Error: Frame digests unequal" << std::endl;
            std::cout << "[Test] [Preprocessor A]: Test Failed" << std::endl;
	    free(digestCalc);
	    return;
	}
    }
    std::cout << "[Test] [Preprocessor A]: Received frame, integrity of frame structure is verified." << std::endl;
    std::cout << "[Test] [Preprocessor A]: Test Passed" << std::endl;
    free(digestCalc);
}

int main(int argc, char **argv)
{
    int myId, numNodes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);
    if (myId == MASTER_ID) {
	std::cout  << "[Test] [Master Node]: Sending first frame of \"test2.mp4\" to preprocessor a" << std::endl;
        sendFrameWithDigest(cv::String("./test2.mp4"));
    } else if (myId == PREPROCESSOR_A) {
	std::cout  << "[Test] [Preprocessor A]: Starting verification test of frame sent by master node." << std::endl;
        receiveAndVerifyFrame();
    }
    MPI_Finalize();
    return 0;
}
