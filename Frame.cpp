#include "mpi.h"
#include <cstdlib>
#include "Frame.h"

static const int MAX_BUFFER_LEN = 8 * 1024 * 1024;

Frame::Frame() :
    cvFrame(),
    index(),
    m_buffer(nullptr)
{
}

Frame::Frame(cv::Mat frame, int frameIndex) :
    cvFrame(frame),
    index(frameIndex),
    m_buffer(nullptr)
{
}

Frame::~Frame()
{
    if (m_buffer != nullptr)
        delete[] m_buffer;
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

    // Send frame index, buffer length, and finally the frame data
    int bufferLen = numBytes + 3 * sizeof(int);
    MPI_Send(&index, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    std::cout << "Sent index value " << index << std::endl;
    MPI_Send(&bufferLen, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    std::cout << "Sent buffer length value " << bufferLen << std::endl;
    MPI_Send(&buffer[0], numBytes + 3 * sizeof(int), MPI_UNSIGNED_CHAR, recipient, 0, MPI_COMM_WORLD);
    std::cout << "Sent all frame data" << std::endl;
}

void Frame::receive(int sender)
{
    // Check if m_buffer was used before calling receive, and if so, delete it
    if (m_buffer != nullptr)
        delete[] m_buffer;
    
    //MPI_Status status;
    int rows, cols, type, channels, count;
    int bufferLen = -1;

    // Read frame index and buffer length
    MPI_Recv(&index, sizeof(int), MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Received index value " << index << std::endl;
    MPI_Recv(&bufferLen, sizeof(int), MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Received buffer length value " << bufferLen << std::endl;
    
    // Read frame data
    if (bufferLen < 0)
        bufferLen = MAX_BUFFER_LEN;
    m_buffer = new unsigned char[bufferLen];
    MPI_Recv(&m_buffer[0], bufferLen, MPI_UNSIGNED_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //MPI_Get_count(&status, MPI_UNSIGNED_CHAR, &count);

    // Copy metadata into rows, cols, and type integers
    memcpy((unsigned char*)&rows, &m_buffer[0], sizeof(int));
    memcpy((unsigned char*)&cols, &m_buffer[sizeof(int)], sizeof(int));
    memcpy((unsigned char*)&type, &m_buffer[2 * sizeof(int)], sizeof(int));

    // Move frame data from buffer into opencv frame structure
    cvFrame = cv::Mat(rows, cols, type, (unsigned char*)&m_buffer[3 * sizeof(int)]);
}

