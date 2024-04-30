#ifndef IMAGE_QUEUE_H
#define IMAGE_QUEUE_H
#include "ImageContainer.h"

_Monitor ImageQueue
{
    int front, back, count;
    uCondition not_empty;
    ImageContainer *queue;

public:
    ImageQueue(int n_images);
    ~ImageQueue();
    void push(ImageContainer image);
    ImageContainer pop();
};

#endif // IMAGE_QUEUE_H
