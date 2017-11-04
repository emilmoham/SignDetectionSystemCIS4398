#ifndef CONSUMER_H
#define CONSUMER_H

#include <queue>

#include "GeneralHeaders.h"
#include "FrameStructs.h"

//WIP

struct buffer{
    sem_t elements;
    std::queue<struct FrameResult> q;
};

void *consume(void *b){
    struct buffer *queue = (struct buffer *)b;

    sem_wait(&(queue->elements));

    /* Definitely a scheduling error here */
    (queue->q).front().print();
    (queue->q).pop();
    /* */

    pthread_exit(NULL);
}

#endif
