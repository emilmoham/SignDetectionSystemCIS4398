#include "Region.h"
#include <utility>

void Region::send(int recipient)
{
    /*
     * Send (in order):
     *     1. Shape field
     *     2. Color bitfield
     *     3. Number of contours
     *     4. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     *
     *     Items 1,2,3 bundled into one array.
     *     Items 4.a.i and 4.a.ii bundled into one array
     */

    int header[3];
    header[0] = static_cast<int>(shapeType);
    header[1] = static_cast<int>(colors);
    header[2] = static_cast<int>(cvContours.size());

    int numPoints = 0;
    int ptData[2];
 
    MPI_Send(&header, 3, MPI_INT, recipient, 0, MPI_COMM_WORLD);
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
     *     3. Number of contours
     *     4. For each contour, 
     *        a) Number of points
     *        b) For each point,
     *            i) x coordinate (int)
     *           ii) y coordinate (int)
     *
     *     Items 1,2,3 bundled into one array.
     *     Items 4.a.i and 4.a.ii bundled into one array
     */

    int header[3];
    int numContours = 0, numPoints = 0;
    int ptData[2];

    MPI_Recv(&header[0], 3, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    shapeType = static_cast<Shape>(header[0]);
    colors = static_cast<Color::Value>(header[1]);
    numContours = header[2];

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

