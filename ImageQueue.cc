#ifndef IMAGE_QUEUE
#define IMAGE_QUEUE
#include "ImageQueue.h"

ImageQueue::ImageQueue(int n_images) {
    front = 0;
    back = 0;
    count = 0;
    queue = new ImageContainer[n_images];
};

ImageQueue::~ImageQueue() {
    delete[] queue;
};

void ImageQueue::push(ImageContainer image) {
    queue[back] = image;
    back++;
    count++;
    not_empty.signal();
};

ImageContainer ImageQueue::pop() {
    if(count == 0) not_empty.wait();
    ImageContainer image = queue[front];
    front++;
    count--;
    return image;
};

#endif // IMAGE_QUEUE