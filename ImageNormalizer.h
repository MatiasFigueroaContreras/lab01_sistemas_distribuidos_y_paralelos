#ifndef IMAGE_NORMALIZER_H
#define IMAGE_NORMALIZER_H
#include "ImageQueue.h"

_Task ImageNormalizer
{
    int n_images;
    double intensity_max;
    ImageQueue & noisy_images_queue;
    ImageQueue & normalized_images_queue;

public:
    ImageNormalizer(int n_images, double intensity_max, ImageQueue &noisy_images_queue, ImageQueue &normalized_images_queue);
    ~ImageNormalizer();

private:
    void main();
};

#endif // IMAGE_NORMALIZER_H