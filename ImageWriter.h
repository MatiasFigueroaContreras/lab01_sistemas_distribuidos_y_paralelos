#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H
#include "ImageQueue.h"
#include <string>

_Task ImageWriter
{
    int n_images;
    std::string prefix;
    ImageQueue & normalized_images_queue;

public:
    ImageWriter(int n_images, std::string prefix, ImageQueue &normalized_images_queue);
    ~ImageWriter();

private:
    void main();
};

#endif // IMAGE_WRITER_H