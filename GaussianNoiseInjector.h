#ifndef GAUSSIAN_NOISE_INJECTOR_H
#define GAUSSIAN_NOISE_INJECTOR_H
#include "ImageQueue.h"

_Task GaussianNoiseInjector{
    int n_images;
    double std_dev;
    ImageQueue & smoothed_images_queue;
    ImageQueue & noisy_images_queue;
public:
    GaussianNoiseInjector(int n_images, float std_dev, ImageQueue &smoothed_images_queue, ImageQueue &noisy_images_queue);
    ~GaussianNoiseInjector();
private:
    double gaussianSample();
    void main();
};

#endif // GAUSSIAN_NOISE_INJECTOR_H