#ifndef FRAMESTRUCTS_H
#define FRAMESTRUCTS_H

//includes
#include "GeneralHeaders.h"

struct Frame{
    int index;
    cv::Mat mat

    //Constructor
    Frame(int i, cv::Mat cvmat) : index(i), mat(cvmat){}

    //Public Functions
    void print(){
        printf("index = %d\n", index);
    }
};

struct Region{
    vector<Point> contour;
    int shape;
    int color;

    //Constructor
    Region(vector<Point> contour): contour(contour){}

    //Public Functions
    void print(){
	if(contour != NULL){
	    printf("has contour. shape=%d, color=%d\n", shape, color);
	}
    }

    int getBoundingBox(){
        
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
