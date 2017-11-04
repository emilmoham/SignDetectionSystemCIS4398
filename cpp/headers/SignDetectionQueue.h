#ifndef SIGNDETECTIONQUEUE_H
#define SIGNDETECTIONQUEUE_H

#include "GeneralHeaders.h"
#include "FrameStructs.h"

//A Single Queue node
//  Contains fields for a struct FrameResult and the next element pointer
struct FrameQueueNode{
    struct FrameQueueNode *next = NULL;
    struct FrameResult *frame_result = NULL;
};


//Custom Queue Data Structure Implementation
//More easily extendible than the standard C++ queue
//  Members front and next are accessors for the queue
//  We implement standard PUSH and POP Functions
//  Assumes all nodes have been allocated on the heap through malloc
struct FrameQueue{
    int size = 0;
    struct FrameQueueNode *front = NULL;
    struct FrameQueueNode *end = NULL;

    void push(struct FrameQueueNode *element){
        if(front == NULL){
            front = element;
            end = element;
        } else {
            struct FrameQueueNode *temp = end;
            end->next = element;
            end = element;
        }
        size++;
    }

    void pop(){
        struct FrameQueueNode *temp;
        temp = front;
        front = front->next;
        free(temp);
    }
};

#endif
