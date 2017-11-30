#include <algorithm>
#include "LogHelper.h"
#include "TextExtractor.h"

TextExtractor::TextExtractor() :
    m_tessAPI(new tesseract::TessBaseAPI()),
    m_initialized(true)
{
    if (m_tessAPI->Init(NULL, "eng"))
    {
        LOG_ERROR("sd_textextraction", "Could not initialize tesseract.");
        m_initialized = false;
    }
}

TextExtractor::~TextExtractor()
{
    m_tessAPI->End();
}

std::string TextExtractor::getText(cv::Mat cvRegion)
{
    if (!m_initialized)
        return std::string();

    // Convert Mat to an 8-bit image
    cv::Mat src8;
    cvRegion.convertTo(cvRegion, CV_8U);
    cv::cvtColor(cvRegion, src8, CV_BGR2GRAY);

    // Open the image with the leptonica library
    Pix *image = convertMat8ToPix(src8);
    m_tessAPI->SetImage(image);

    const char *text = m_tessAPI->GetUTF8Text(); 
    std::string result(text);
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());

    LOG_DEBUG("sd_textextraction", "Detected the text: \"", result, "\" from the given region");

    // Free resources
    delete[] text;
    pixDestroy(&image);

    return result;
}

Pix *TextExtractor::convertMat8ToPix(cv::Mat &mat8)
{
    Pix *image = pixCreate(mat8.size().width, mat8.size().height, 8);
    for (int y = 0; y < mat8.rows; ++y)
    {
        for (int x = 0; x < mat8.cols; ++x)
        {
            pixSetPixel(image, x, y, (l_uint32)mat8.at<uchar>(y,x));
        }
    }
    return image;
}

