#ifndef GAUSSIAN_NOISE_INJECTOR_H
#define GAUSSIAN_NOISE_INJECTOR_H
#include "ImageQueue.h"
#include <random>

// Tarea encargada de agregar ruido gaussiano a las imágenes
// - n_images: número de imágenes a las que se les va a agregar ruido
// - std_dev: desviación estándar del ruido gaussiano
// - smoothed_images_queue: Monitor tipo cola donde se van a obtener las imágenes suavizadas
// - noisy_images_queue: Monitor tipo cola donde se van a añadir las imágenes con ruido
_Task GaussianNoiseInjector{
    int n_images;
    double std_dev;
    ImageQueue & smoothed_images_queue;
    ImageQueue & noisy_images_queue;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
public:
    GaussianNoiseInjector(int n_images, float std_dev, ImageQueue &smoothed_images_queue, ImageQueue &noisy_images_queue);
    ~GaussianNoiseInjector();
private:
    ImageContainer addNoise(ImageContainer image);
    void main();
};

#endif // GAUSSIAN_NOISE_INJECTOR_H