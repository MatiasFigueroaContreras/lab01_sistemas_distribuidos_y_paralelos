#ifndef IMAGE_READER_H
#define IMAGE_READER_H
#include <string>
#include "ImageQueue.h"

_Task ImageReader
{
    int n_images;
    std::string prefix;
    ImageQueue & images_queue;

public:
    ImageReader(int n_images, std::string prefix, ImageQueue &images_queue);
    ~ImageReader();

private:
    void main();
};

#endif // IMAGE_READER_H