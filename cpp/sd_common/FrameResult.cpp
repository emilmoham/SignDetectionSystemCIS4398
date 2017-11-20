#include "mpi.h"
#include <cstdlib>
#include "Frame.h"
#include "Region.h"
#include "LogHelper.h"

static const int MAX_FRAME_BUFFER_LEN = 8 * 1024 * 1024;

FrameResult::FrameResult() :
    frameStruct(),
    region(0)
    //m_buffer(nullptr),
    //m_bufferLen(0)
{}

FrameResult::FrameResult(Frame frame, Region reg) :
    frameStruct(frame),
    region(reg)
    //m_buffer(nullptr),
    //m_bufferLen(0)
{}

FrameResult::~FrameResult()
{
    if (m_buffer != nullptr)
        delete[] m_buffer;
}

// big TODO here
void FrameResult::send(int recipient)
{
    //unsigned char buffer[MAX_FRAME_BUFFER_LEN];
    if (m_buffer == nullptr)
        m_buffer = new unsigned char[MAX_FRAME_BUFFER_LEN];
    LOG_DEBUG("serializable", "Frame::send(recipient=", recipient, "): allocated memory for buffer.");
    int rows = cvFrame.rows;
    int cols = cvFrame.cols;
    int type = cvFrame.type();
    int channels = cvFrame.channels();

    // Copy frame metadata into buffer
    memcpy(&m_buffer[0], (unsigned char*)&rows, sizeof(int));
    memcpy(&m_buffer[sizeof(int)], (unsigned char*)&cols, sizeof(int));
    memcpy(&m_buffer[2 * sizeof(int)], (unsigned char*)&type, sizeof(int));
    LOG_DEBUG("serializable", "Copied metadata into frame sending buffer");

    int numBytes = rows * cols * channels;
    if (!cvFrame.isContinuous())
        cvFrame = cvFrame.clone();

    // Copy frame data into buffer
    memcpy(&m_buffer[3 * sizeof(int)], cvFrame.data, numBytes);
    LOG_DEBUG("serializable", "Copied cv::Mat data into frame sending buffer"); 

    // Send frame index, buffer length, and finally the frame data
    int bufferLen = numBytes + 3 * sizeof(int);
    MPI_Send(&index, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    LOG_DEBUG("serializable", "Sent index value ", index);
    MPI_Send(&bufferLen, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    LOG_DEBUG("serializable", "Sent buffer length value ", bufferLen);
    MPI_Send(&m_buffer[0], numBytes + 3 * sizeof(int), MPI_UNSIGNED_CHAR, recipient, 0, MPI_COMM_WORLD);
    LOG_DEBUG("serializable", "Sent all frame data", bufferLen);
}

// big TODO here
void FrameResult::receive(int sender)
{
    
    //MPI_Status status;
    int rows, cols, type, channels, count;
    int bufferLen = -1;

    // Read frame index and buffer length
    MPI_Recv(&index, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    LOG_DEBUG("serializable", "Received index value ", index);
    MPI_Recv(&bufferLen, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    LOG_DEBUG("serializable", "Received buffer length value of ", bufferLen);

    if (bufferLen > m_bufferLen)
    {
        delete[] m_buffer;
        m_buffer = new unsigned char[bufferLen];
        m_bufferLen = bufferLen;
    }
    MPI_Recv(&m_buffer[0], bufferLen, MPI_UNSIGNED_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Copy metadata into rows, cols, and type integers
    memcpy((unsigned char*)&rows, &m_buffer[0], sizeof(int));
    memcpy((unsigned char*)&cols, &m_buffer[sizeof(int)], sizeof(int));
    memcpy((unsigned char*)&type, &m_buffer[2 * sizeof(int)], sizeof(int));

    // Move frame data from buffer into opencv frame structure
    cvFrame = cv::Mat(rows, cols, type, (unsigned char*)&m_buffer[3 * sizeof(int)]);
}

