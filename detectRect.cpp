int main()
{
    cv::Mat input = cv::imread("..");

    // convert to grayscale 
    cv::Mat gray;
    cv::cvtColor(input,gray, CV_BGR2GRAY);

    // compute mask 
    cv::Mat mask;
    cv::threshold(gray, mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    /// Draw contours and find biggest contour
    int biggestContourIdx = -1;
    float biggestContourArea = 0;
    cv::Mat drawing = cv::Mat::zeros( mask.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar(0, 100, 0);
        drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point() );

        float ctArea= cv::contourArea(contours[i]);
        if(ctArea > biggestContourArea)
        {
            biggestContourArea = ctArea;
            biggestContourIdx = i;
        }
    }

    // if no contour found
    if(biggestContourIdx < 0)
    {
        std::cout << "no contour found" << std::endl;
        return 1;
    }

    // compute the bounding rect of the biggest contour
    cv::Rect boundingBox = cv::minAreaRect(contours[biggestContourIdx]);
    

   // draw the rect
    cv::Point2f corners[4];
    boundingBox.points(corners);
    cv::line(drawing, corners[0], corners[1], cv::Scalar(255,255,255));
    cv::line(drawing, corners[1], corners[2], cv::Scalar(255,255,255));
    cv::line(drawing, corners[2], corners[3], cv::Scalar(255,255,255));
    cv::line(drawing, corners[3], corners[0], cv::Scalar(255,255,255));

    // display
    cv::imshow("input", input);
    cv::imshow("drawing", drawing);
    cv::waitKey(0);

    return 0;
}
