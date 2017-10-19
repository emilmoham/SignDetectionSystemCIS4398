#include "headers/GeneralHeaders.h"
#include "headers/FrameStructs.h"
#include "headers/consumer.h"
/*
This test currently runs, but is super broken. There's some memory overread
or over write somewhere.

I believe that we will need to implement our own version of a queue because
the current implementation is not extendable through a heap allocated
object.
*/


#define NUM_THREADS 1

struct buffer *init();

using namespace std;

int main(int argc, char **argv){
    //Threaed information
    pthread_t threads[NUM_THREADS];
    int rc;

    //Lock and Queue container
    struct buffer buff;

    //Allocate space for and initalize buffer
    //buff = &(init());

    //initalize semaphore
    //sem_init(&(buff->mutex), 0, 1);
    sem_init(&(buff.elements), 0, 0);
    int current_elements;

    //Create Consumer threads
    for(int i = 0; i < NUM_THREADS; i++){
        printf("main(): creating thread, %d\n", i);
        rc = pthread_create(&threads[i], NULL, consume, (void *)&buff);

        if(rc){
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    //Add elements to queue of Frame struct
    for(int i = 0; i < NUM_THREADS; i++){
        //sem_getvalue(&(buff->elements), &current_elements);
        printf("%d\n", current_elements);
        struct Frame frame_obj(i);
        struct Region region_obj(i, i+1, i+2, i+3);
        struct FrameResult FrameResult_obj(frame_obj, region_obj);
        (buff.q).push(FrameResult_obj);
        sem_post(&(buff.elements));
    }

    pthread_exit(NULL);
}

struct buffer *init(){
    struct buffer *b;
    if((b=(struct buffer *)malloc(sizeof(struct buffer))) == NULL){
        fprintf(stderr, "Error Initializing buffer\n");
        return NULL;
    }
    return b;
}
