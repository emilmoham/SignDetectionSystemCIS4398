#include "Region.h"
#include <utility>
#include <mpi.h>

void Region::send(int recipient)
{
    /*
     * Send (in order):
     *     1. Shape field
     *     2. Color bitfield
     *     3. Sign type field
     *     4. Number of contours
     *     5. Sign text field
     *        a) Sign text length
     *        b) Sign text
     *     6. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     *
     *     Items 1,2,3,4,5a bundled into one array.
     *     Items 6.a.i and 6.a.ii bundled into one array
     */

    int header[5];
    header[0] = static_cast<int>(shapeType);
    header[1] = static_cast<int>(colors);
    header[2] = static_cast<int>(signType);
    header[3] = static_cast<int>(cvContours.size());

    int textLen = static_cast<int>(signText.size());
    header[4] = textLen;

    int numPoints = 0;
    int ptData[2];
 
    MPI_Send(&header, 5, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    
    if (textLen > 0)
        MPI_Send(const_cast<char*>(signText.c_str()), signText.size(), MPI_CHAR, recipient, 0, MPI_COMM_WORLD);

    for (auto &contour : cvContours)
    {
        numPoints = static_cast<int>(contour.size());
        MPI_Send(&numPoints, 1, MPI_INT, recipient, 0, MPI_COMM_WORLD);
        
        for (auto &pt : contour)
        {
            ptData[0] = pt.x;
            ptData[1] = pt.y;
            MPI_Send(&ptData, 2, MPI_INT, recipient, 0, MPI_COMM_WORLD);
        }
    }
}

void Region::receive(int sender)
{
    cvContours.clear();

    /*
     * Receive (in order):
     *     1. Shape field
     *     2. Color bitfield
     *     3. Sign type field
     *     4. Number of contours
     *     5. Sign text field
     *        a) Sign text length
     *        b) Sign text
     *     6. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     */

    int header[5];
    int numContours = 0, numPoints = 0, textLen = 0;
    int ptData[2];

    MPI_Recv(&header[0], 5, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    shapeType = static_cast<Shape>(header[0]);
    colors = static_cast<Color::Value>(header[1]);
    signType = static_cast<SignType>(header[2]);
    numContours = header[3];
    textLen = header[4];

    if (textLen > 0)
    {
        char *textData = new char[textLen + 1]();
        MPI_Recv(textData, textLen, MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        signText = std::string(textData);
        delete[] textData;
    }

    for (int i = 0; i < numContours; ++i)
    {
        MPI_Recv(&numPoints, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::vector<cv::Point> points;
        for (int j = 0; j < numPoints; ++j)
        {
            MPI_Recv(&ptData, 2, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            points.push_back(cv::Point(ptData[0], ptData[1])); 
        }
        cvContours.push_back(std::move(points));
    }
}

