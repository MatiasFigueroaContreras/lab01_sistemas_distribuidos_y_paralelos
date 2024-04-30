#ifndef IMAGE_SMOOTHER_H
#define IMAGE_SMOOTHER_H
#include "ImageQueue.h"

_Task ImageSmoother
{
    int n_images;
    float theta_fraction;
    ImageQueue & images_queue;
    ImageQueue & smoothed_images_queue;

public:
    ImageSmoother(int n_images, float theta_fraction, ImageQueue &images_queue, ImageQueue &smoothed_images_queue);
    ~ImageSmoother();

private:
    double **calcKernel();
    double *convolveImage(ImageContainer image, double **kernel);
    void main();
};

#endif // IMAGE_SMOOTHER_H