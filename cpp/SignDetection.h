#ifndef SIGNDETECTION_H
#define SIGNDETECTION_H

//includes
#include <stdio.h>
#include <queue>
//#include <opencv2/opencv.hpp>
//TODO Create CMakefile for compiling with OpenCV2
struct Frame{
    int index;
    //cv::Mat image

    Frame(int i) : index(i){}

    //Public Functions
    void print(){
        printf("index = %d\n", index);
    }
};

struct Region{
    //Rectangle Definition Members
    int x, y, w, h;

    //Constructor
    Region(int x, int y, int w, int h): x(x), y(y), w(w), h(h){}

    //Public Functions
    void print(){
        printf("x = %d\n", x);
        printf("y = %d\n", y);
        printf("w = %d\n", w);
        printf("h = %d\n", h);
    }
};

struct FrameResult{
    struct Frame f;
    struct Region r; //TODO change to List data structure

    //Constructor
    FrameResult(struct Frame f, struct Region r) : f(f), r(r){}

    //Public functions
    void print(){
        f.print();
        r.print();
    }
};

#endif
