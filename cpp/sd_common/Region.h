#ifndef __REGION_H_
#define __REGION_H_

#include "opencv2/opencv.hpp"
#include "Passable.h"
#include "Colors.h"
#include "Shapes.h"

#include <vector>

/**
 * @class Region
 * @brief Contains data about a region of interest in a single frame.
 */
class Region : public Passable
{
public:
    /// Vector of points making up the contour. Point structure contains fields for x and y coordinates
    std::vector<cv::Point> cvContour;

    /// Type of shape 
    Shape shapeType;

    /// Bitfield of colors detected within the region
    Color::Value colors;

public:
    /// Sends the region data to the given recipient
    virtual void send(int recipient) override;

    /// Receives the region data from the given sender
    virtual void receive(int sender) override;
};

#endif //__REGION_H_

