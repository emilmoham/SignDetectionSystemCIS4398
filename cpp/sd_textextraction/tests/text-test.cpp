#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <iostream>

Pix *mat8ToPix(cv::Mat *mat8)
{
    Pix *pixd = pixCreate(mat8->size().width, mat8->size().height, 8);
    for(int y=0; y<mat8->rows; y++) {
        for(int x=0; x<mat8->cols; x++) {
            pixSetPixel(pixd, x, y, (l_uint32) mat8->at<uchar>(y,x));
        }
    }
    return pixd;
}

int main(int argc, char **argv)
{
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open image with opencv, convert to Pix structure to be interpreted by the tesseract library
    cv::Mat src = cv::imread("numbers.jpg", CV_LOAD_IMAGE_COLOR);
    if (!src.data)
    {
        std::cout << "Could not open image data file" << std::endl;
        api->End();
        return 0;
    }

    // Convert opencv Mat to an 8-bit image
    cv::Mat src8;
    src.convertTo(src, CV_8U);
    cv::cvtColor(src, src8, CV_BGR2GRAY);

    // Open input image with leptonica library
    Pix *image = mat8ToPix(&src8);
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);
    std::cout << "Expected output: 55" << std::endl;

    if (outText[0] == '5' && outText[1] == '5')
        std::cout << "Test Passed" << std::endl;
    else
        std::cout << "Test Failed" << std::endl;

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);

    return 0;
}
