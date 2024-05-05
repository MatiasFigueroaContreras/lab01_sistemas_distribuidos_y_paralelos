#ifndef GAUSSIAN_NOISE_INJECTOR
#define GAUSSIAN_NOISE_INJECTOR
#include "GaussianNoiseInjector.h"
#include <iostream>

// Constructor de la tarea GaussianNoiseInjector
// - n_images: número de imágenes a las que se les va a agregar ruido
// - std_dev: desviación estándar del ruido gaussiano
// - smoothed_images_queue: Monitor tipo cola donde se van a obtener las imágenes suavizadas
// - noisy_images_queue: Monitor tipo cola donde se van a añadir las imágenes con ruido
GaussianNoiseInjector::GaussianNoiseInjector(int n_images, float std_dev, ImageQueue &smoothed_images_queue, ImageQueue &noisy_images_queue)
    : n_images(n_images), std_dev(std_dev), smoothed_images_queue(smoothed_images_queue), noisy_images_queue(noisy_images_queue)
{
    generator = std::default_random_engine();
    distribution = std::normal_distribution<double>(0.0, std_dev);
}

// Destructor de la tarea GaussianNoiseInjector
GaussianNoiseInjector::~GaussianNoiseInjector()
{
}


// Método para agregar ruido gaussiano a una imagen
// - image: imagen a la que se le va a agregar ruido
// - retorna la imagen con ruido
ImageContainer GaussianNoiseInjector::addNoise(ImageContainer image)
{
    double *noisy_image = new double[image.size[0] * image.size[1]];
    double *smoothed_image = image.image;

    for (int j = 0; j < image.size[0] * image.size[1]; j++)
    {
        noisy_image[j] = smoothed_image[j] + distribution(generator);
    }
    image.image = noisy_image;
    delete[] smoothed_image;
    return image;
}

// Método donde se ejecuta la hebra de la tarea GaussianNoiseInjector
//  esta agrega ruido gaussiano a las imágenes y las añade al monitor noisy_images_queue
void GaussianNoiseInjector::main()
{

    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = smoothed_images_queue.pop();
        ImageContainer noisy_image = addNoise(image);
        noisy_images_queue.push(noisy_image);
    }
}

#endif // GAUSSIAN_NOISE_INJECTOR