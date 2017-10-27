#include "mpi.h"
#include "openssl/sha.h"
#include "Frame.h"
#include "NodeID.h"

using namespace cv;

// Calculates the SHA256 digest of the frame, storing it into the output buffer
void getDigest(const Mat &frameMat, unsigned char *output)
{
    int frameLen = frameMat.rows * frameMat.cols * frameMat.channels(); 
    SHA256_CTX sha256;
    SHA256_Update(&sha256, frameMat.data, frameLen);
    SHA256_Final(output, &sha256);
}

void sendFrameWithDigest(cv::String file) {
    // Open default camera
    VideoCapture cap(file);

    // Handle errors if any
    if (!cap.isOpened()) {
        std::cout << "Failed to open video file" << std::endl;
        return;
    }

    // Extract and send the first frame, along with its SHA256 digest
    Frame frameStruct;
    cap >> frameStruct.cvFrame;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    getDigest(frameStruct.cvFrame, &hash[0]);

    MPI_Send(&hash, SHA256_DIGEST_LENGTH, MPI_UNSIGNED_CHAR, PREPROCESSOR_A, 0, MPI_COMM_WORLD);
    frameStruct.send(PREPROCESSOR_A);
}

// Reads a frame structure from the master node, verifying its integrity by comparing the
// given digest value of the frame to the calculated value after receiving the frame data
void receiveAndVerifyFrame() {
    MPI_Status status;

    // First read the digest value
    unsigned char hashGiven[SHA256_DIGEST_LENGTH];
    MPI_Recv(&hashGiven, SHA256_DIGEST_LENGTH, MPI_UNSIGNED_CHAR, MASTER_ID, 0, MPI_COMM_WORLD, &status);
    std::unique_ptr<frame> frameStruct = receiveFrame();

    // Calculate the frame's digest
    unsigned char hashCalc[SHA256_DIGEST_LENGTH];
    getDigest(frameStruct->frame, &hashCalc[0]);

    // Compare digest values
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        if (hashGiven[i] != hashCalc[i]) {
	    std::cout << "Error: Digests unequal. Aborting." << std::endl;
	    return;
	}
    }
    std::cout << "Received frame, integrity of frame structure is verified." << std::endl;
}

int main(int argc, char **argv)
{
    int myId, numNodes;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myId);
    if (myId == MASTER_ID) {
        sendFrameWithDigest(cv::String("test2.mp4"));
    } else {
        receiveAndVerifyFrame();
    }
    return 0;
}
