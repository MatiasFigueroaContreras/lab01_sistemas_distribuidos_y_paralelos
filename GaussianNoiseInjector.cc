#ifndef GAUSSIAN_NOISE_INJECTOR
#define GAUSSIAN_NOISE_INJECTOR
#include "GaussianNoiseInjector.h"
#include <random>
#include <iostream>

GaussianNoiseInjector::GaussianNoiseInjector(int n_images, float std_dev, ImageQueue &smoothed_images_queue, ImageQueue &noisy_images_queue)
    : n_images(n_images), std_dev(std_dev), smoothed_images_queue(smoothed_images_queue), noisy_images_queue(noisy_images_queue)
{
}

GaussianNoiseInjector::~GaussianNoiseInjector()
{
}

double GaussianNoiseInjector::gaussianSample()
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, std_dev);
    return distribution(generator);
}

void GaussianNoiseInjector::main()
{
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = smoothed_images_queue.pop();
        std::cout << "Noising Image " << image.number << std::endl;
        double *noisy_image = new double[image.size[0] * image.size[1]];
        double *smoothed_image = image.image;
        for (int j = 0; j < image.size[0] * image.size[1]; j++)
        {
            noisy_image[j] = smoothed_image[j] + gaussianSample();
        }
        image.image = noisy_image;
        noisy_images_queue.push(image);
        delete[] smoothed_image;
    }
}

#endif // GAUSSIAN_NOISE_INJECTOR