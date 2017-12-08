/**
 * Shape detection test
 * Loads a series of images, each containing a single shape, calling the shape detection method
 * and comparing the results to the known shapes.
 */
#include "../headers/OpenCVHeaders.h"
#include <cmath>

#include "Contour.h"
#include "../sd_shapedetection/ShapeDetection.h"
#include "../sd_render/Render.h"


enum class ShapeResult
{
    Circle    = 10,
    Triangle  = 30,
    Rectangle = 40,
    Pentagon  = 50,
    Hexagon   = 60
};

std::vector<ShapeResult> getShapesFor(cv::Mat src)
{
    std::vector<std::vector<cv::Point> > contours;
    contours = sd_getContours(src);
    std::vector<cv::Point> approx;
    cv::Mat dst = src.clone();
        
    std::vector<ShapeResult> results;
    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
            
        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;

        int shape = sd_getShape(approx, contours[i]);
        if (shape < 10 || shape > 60)
            std::cout << "Unknown shape detected" << std::endl;
        else
            results.push_back(static_cast<ShapeResult>(shape));
    }
    return results;
}

bool testCircle()
{
    cv::Mat src = cv::imread("circle.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "[Test]: Circle test - could not read image data." << std::endl;
        return false;
    }
    auto results = getShapesFor(src);
    for (auto shape : results)
    {
        if (shape == ShapeResult::Circle)
            return true;
    }
    return false;
}

bool testTriangle()
{
    cv::Mat src = cv::imread("triangle.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "[Test]: Triangle test - could not read image data." << std::endl;
        return false;
    }
    auto results = getShapesFor(src);
    for (auto shape : results)
    {
        if (shape == ShapeResult::Triangle)
            return true;
    }
    return false;
}

bool testRectangle()
{
    cv::Mat src = cv::imread("rectangle.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "[Test]: Rectangle test - could not read image data." << std::endl;
        return false;
    }
    auto results = getShapesFor(src);
    for (auto shape : results)
    {
        if (shape == ShapeResult::Rectangle)
            return true;
    }
    return false;
}

bool testPentagon()
{
    cv::Mat src = cv::imread("pentagon.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "[Test]: Pentagon test - could not read image data." << std::endl;
        return false;
    }
    auto results = getShapesFor(src);
    for (auto shape : results)
    {
        if (shape == ShapeResult::Rectangle)
            return true;
    }
    return false;
}

bool testHexagon()
{
    cv::Mat src = cv::imread("hexagon.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "[Test]: Hexagon test - could not read image data." << std::endl;
        return false;
    }
    auto results = getShapesFor(src);
    for (auto shape : results)
    {
        if (shape == ShapeResult::Hexagon)
            return true;
    }
    return false;
}


int main()
{   
    std::string passedString = "passed", failedString = "failed";

    int numPassed = 0, numFailed = 0;
    bool ok = testCircle();
    std::cout << "[Test]: Circle detection - ";
    if (ok)
    {
        ++numPassed;
        std::cout << "passed\n";
    }
    else
    {
        ++numFailed;
        std::cout << "failed\n";
    }

    ok = testTriangle();
    std::cout << "[Test]: Triangle detection - ";
    if (ok)
    {
        ++numPassed;
        std::cout << "passed\n";
    }
    else
    {
        ++numFailed;
        std::cout << "failed\n";
    }

    ok = testRectangle();
    std::cout << "[Test]: Rectangle detection - ";
    if (ok)
    {
        ++numPassed;
        std::cout << "passed\n";
    }
    else
    {
        ++numFailed;
        std::cout << "failed\n";
    }

    ok = testPentagon();
    std::cout << "[Test]: Pentagon detection - ";
    if (ok)
    {
        ++numPassed;
        std::cout << "passed\n";
    }
    else
    {
        ++numFailed;
        std::cout << "failed\n";
    }

    ok = testHexagon();
    std::cout << "[Test]: Hexagon detection - ";
    if (ok)
    {
        ++numPassed;
        std::cout << "passed\n";
    }
    else
    {
        ++numFailed;
        std::cout << "failed\n";
    }

    std::cout << std::endl;

    std::cout << "Results: " << numPassed << " tests passed, " << numFailed << " tests failed." << std::endl;
    return 0;
}
