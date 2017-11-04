#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void drawStuff();
void drawAllTriangles(Mat&, const vector< vector<Point> >&);

Mat img_rgb,img_gray,canny_output,drawing;

int thresh = 100;
int max_thresh = 255;

int main(){
    img_rgb  = imread("../road-signs.jpg");
    cvtColor(img_rgb,img_gray,CV_RGB2GRAY);
    imshow("InputImage",img_rgb);
    drawStuff();
    waitKey(0);
}

void drawStuff(){
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Canny( img_gray, canny_output, thresh, thresh*2, 3 );
    imshow("Canny",canny_output);
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    drawing = Mat::zeros( canny_output.size(), CV_8UC3 );

    drawAllTriangles(drawing,contours);
    imshow("Triangles",drawing);
}

void drawAllTriangles(Mat& img, const vector< vector<Point> >& contours){
    vector<Point> approxTriangle;
    for(size_t i = 0; i < contours.size(); i++){
        approxPolyDP(contours[i], approxTriangle, arcLength(Mat(contours[i]), true)*0.05, true);
        if(approxTriangle.size() == 3){
            drawContours(img, contours, i, Scalar(0, 255, 255), CV_FILLED); // fill GREEN
            vector<Point>::iterator vertex;
            for(vertex = approxTriangle.begin(); vertex != approxTriangle.end(); ++vertex){
                circle(img, *vertex, 3, Scalar(0, 0, 255), 1);
            }
        }
    }
}
