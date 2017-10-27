#include "mpi.h"
#include <cstdlib>
#include "Frame.h"

static const int MAX_BUFFER_LEN = 8 * 1024 * 1024;

Frame::Frame(cv::Mat frame, int frameIndex) :
    cvFrame(frame),
    index(frameIndex)
{
}

void Frame::send(int recipient)
{
    unsigned char buffer[MAX_BUFFER_LEN];
    int rows = cvFrame.rows;
    int cols = cvFrame.cols;
    int type = cvFrame.type();
    int channels = cvFrame.channels();

    // Copy frame metadata into buffer
    memcpy(&buffer[0], (unsigned char*)&rows, sizeof(int));
    memcpy(&buffer[sizeof(int)], (unsigned char*)&cols, sizeof(int));
    memcpy(&buffer[2 * sizeof(int)], (unsigned char*)&type, sizeof(int));

    int numBytes = rows * cols * channels;
    if (!cvFrame.isContinuous())
        cvFrame = cvFrame.clone();

    // Copy frame data into buffer
    memcpy(&buffer[3 * sizeof(int)], cvFrame.data, numBytes);

    // Send frame index, followed by the frame data
    MPI_Send(&cvFrame.index, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    MPI_Send(&buffer, numBytes + 3 * sizeof(int), MPI_UNSIGNED_CHAR, recipient, 0, MPI_COMM_WORLD);
}

void Frame::receive(int sender)
{
    MPI_Status status;
    int rows, cols, type, channels, count;

    // Read frame index
    MPI_Recv(&index, sizeof(int), MPI_INT, sender, 0, MPI_COMM_WORLD, &status);
    
    // Read frame data
    unsigned char buffer[MAX_BUFFER_LEN];
    MPI_Recv(&buffer, sizeof(buffer), MPI_UNSIGNED_CHAR, sender, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_UNSIGNED_CHAR, &count);

    // Copy metadata into rows, cols, and type integers
    memcpy((unsigned char*)&rows, &buffer[0], sizeof(int));
    memcpy((unsigned char*)&cols, &buffer[sizeof(int)], sizeof(int));
    memcpy((unsigned char*)&type, &buffer[2 * sizeof(int)], sizeof(int));

    // Move frame data from buffer into opencv frame structure
    cvFrame = cv::Mat(rows, cols, type, (unsigned char*)&buffer[3 * sizeof(int)]);
}

