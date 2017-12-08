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
     *     5. Size of vector<Vec4i>
     *     6. Size of vector<Rect>
     *     7. Sign text field
     *        a) Sign text length
     *        b) Sign text
     *     8. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     */

    int header[7];
    header[0] = static_cast<int>(shapeType);
    header[1] = static_cast<int>(colors);
    header[2] = static_cast<int>(signType);
    header[3] = static_cast<int>(cvContours.size());
    header[4] = static_cast<int>(vec4i.size());
    header[5] = static_cast<int>(rects.size());

    int textLen = static_cast<int>(signText.size());
    header[6] = textLen;

    int numPoints = 0;
    int ptData[2];
 
    MPI_Send(&header, 7, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    
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

    int vecBuffer[4];
    for (auto &vec : vec4i)
    {
        for (int i = 0; i < 4; ++i)
            vecBuffer[i] = vec[i];
	MPI_Send(&vecBuffer, 4, MPI_INT, recipient, 0, MPI_COMM_WORLD);
    }

    double rectBuffer[4];
    for (auto &rect : rects)
    {
        rectBuffer[0] = rect.x;
	rectBuffer[1] = rect.y;
	rectBuffer[2] = rect.width;
	rectBuffer[3] = rect.height;
	MPI_Send(&rectBuffer, 4, MPI_DOUBLE, recipient, 0, MPI_COMM_WORLD);
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
     *     5. Size of vector<Vec4i>
     *     6. Size of vector<Rect>
     *     7. Sign text field
     *        a) Sign text length
     *        b) Sign text
     *     8. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     */

    int header[7];
    int numContours = 0, numVec4i = 0, numRects = 0, numPoints = 0, textLen = 0;
    int ptData[2];

    MPI_Recv(&header[0], 7, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    shapeType = static_cast<Shape>(header[0]);
    colors = static_cast<Color::Value>(header[1]);
    signType = static_cast<SignType>(header[2]);
    numContours = header[3];
    numVec4i = header[4];
    numRects = header[5];
    textLen = header[6];

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

    int vecBuffer[4];
    cv::Vec4i vec;
    for (int i = 0; i < numVec4i; ++i)
    {
        MPI_Recv(&vecBuffer, 4, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	for (int j = 0; j < 4; ++j)
            vec[j] = vecBuffer[j];
	vec4i.push_back(vec);
    }

    double rectBuffer[4];
    cv::Rect_<double> rect;
    for (int i = 0; i < numRects; ++i)
    {
        MPI_Recv(&rectBuffer, 4, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	rect.x = rectBuffer[0];
	rect.y = rectBuffer[1];
	rect.width = rectBuffer[2];
	rect.height = rectBuffer[3];
	rects.push_back(rect);
    }
}

