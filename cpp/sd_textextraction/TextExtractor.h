#ifndef __TEXT_EXTRACTOR_H_
#define __TEXT_EXTRACTOR_H_

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @class TextExtractor
 * @brief Used to convert regions of a frame containing text into a string format
 */
class TextExtractor
{
public:
    /// Constructs the text extractor, initializing the tesseract base API
    TextExtractor();

    /// Text extractor destructor, frees resources given to the tesseract base API
    ~TextExtractor();

    /**
     * @brief Searches the given region for alphanumeric data, converting it into a string
     * @param cvRegion The area potentially containing text. Should only be the detected sign, converted into a cv::Mat structure
     * @returns A string containing the text in the region, or an empty string if no text was found
     */
    std::string getText(cv::Mat cvRegion);

private:
    /**
     * @brief Converts the 8-bit cv::Mat structure into a Pix structure for text extraction
     * @param mat8 A reference to the 8-bit cv Mat structure
     * @returns A Pix structure, equivalent to the given 8-bit mat
     */
    Pix *convertMat8ToPix(cv::Mat &mat8);

private:
    /// Tesseract API object used for text extraction
    tesseract::TessBaseAPI *m_tessAPI;

    /// Stores the status of the tesseract api - if true, tesseract can be used for text extraction. Otherwise there was an error
    bool m_initialized;
};


#endif //__TEXT_EXTRACTOR_H_

