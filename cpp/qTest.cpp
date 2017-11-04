#include "headers/GeneralHeaders.h"
#include "headers/SignDetectionQueue.h"

using namespace std;

struct FrameQueueNode *create_FQN(struct FrameResult* fr);
struct FrameResult *create_FrameResult(int index, int x, int y, int w, int h);

int main(int argc, char **argv){

    struct FrameQueue q;
    struct FrameQueueNode* fqn;
    struct FrameResult *fr;

    for(int i = 0; i < 10; i++){
        fr = create_FrameResult(i, i + 1, i + 3, i + 5, i + 7);
        fqn = create_FQN(fr);
        q.push(fqn);
    }

    struct FrameQueueNode* current = q.front;

    while(current != NULL){
        current->frame_result->print();
        free(current->frame_result);
        current = current->next;
        q.pop();
        printf("\n");
    }

    return 0;
}

struct FrameQueueNode *create_FQN(struct FrameResult* fr){
    struct FrameQueueNode *node;

    if((node = (struct FrameQueueNode*)malloc(sizeof(struct FrameQueueNode))) == NULL){
        fprintf(stderr, "Error: Could not allocate space for new FQNode\n");
        return NULL;
    }

    node->frame_result = fr;

    return node;
}

struct FrameResult *create_FrameResult(int index, int x, int y, int w, int h){
    struct FrameResult *element;

    if((element = (struct FrameResult*)malloc(sizeof(struct FrameResult))) == NULL){
        fprintf(stderr, "Error: could not allocate space for new FR Element");
        return NULL;
    }

    struct Frame frame(index);
    struct Region region(x,y,w,h);

    element->f = frame;
    element->r = region;

    return element;
}
