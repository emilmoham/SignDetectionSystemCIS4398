#ifndef __REGION_H_
#define __REGION_H_

#include <opencv2/opencv.hpp>

#include "Passable.h"
#include "Colors.h"
#include "Shapes.h"
#include "SignType.h"

#include <string>
#include <vector>

/**
 * @class Region
 * @brief Contains data about a region of interest in a single frame.
 */
class Region : public Passable
{
public:
    /// Vector of contours. Point structure within contour only contains fields for x and y coordinates
    std::vector< std::vector<cv::Point> > cvContours;

    /// Hierarchy used for finding contours
    std::vector<cv::Vec4i> hierarchy;

    /// Bounding rects
    std::vector<cv::Rect> rects;

    /// Type of shape 
    Shape shapeType;

    /// Bitfield of colors detected within the region
    Color::Value colors;

    /// Type of sign (can be of type invalid or any other type in the SignType enum)
    SignType signType;

    /// Text extracted from the sign (can be an empty string)
    std::string signText;

public:
    Region() = default;

    /// Copy constructor
    Region(const Region &other)
    {
        cvContours = other.cvContours;
        hierarchy = other.hierarchy;
        rects = other.rects;
        shapeType = other.shapeType;
        colors = other.colors;
        signType = other.signType;
        signText = other.signText;
    }

    /// Move constructor
    Region(Region &&other)
    {
        cvContours = std::move(other.cvContours);
        hierarchy = std::move(other.hierarchy);
        rects = std::move(other.rects);
        shapeType = other.shapeType;
        colors = other.colors;
        signType = other.signType;
        signText = other.signText;
    }

    /// Copy assignment operator
    Region &operator=(const Region &other)
    {
        cvContours = other.cvContours;
   	    hierarchy = other.hierarchy;
        rects = other.rects;
        shapeType = other.shapeType;
        colors = other.colors;
        signType = other.signType;
        signText = other.signText;
	    return *this;
    }

    /// Move assignment operator
    Region &operator=(Region &&other)
    {
        cvContours = std::move(other.cvContours);
        hierarchy = std::move(other.hierarchy);
        rects = std::move(other.rects);
        shapeType = other.shapeType;
        colors = other.colors;
        signType = other.signType;
        signText = other.signText;
	    return *this;
    }

public:
    /// Sends the region data to the given recipient
    virtual void send(int recipient) override;

    /// Receives the region data from the given sender
    virtual void receive(int sender) override;
};

#endif //__REGION_H_

