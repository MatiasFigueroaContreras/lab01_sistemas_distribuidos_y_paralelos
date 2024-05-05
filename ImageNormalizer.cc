#ifndef IMAGE_NORMALIZER
#define IMAGE_NORMALIZER
#include "ImageNormalizer.h"
#include <iostream>

// Constructor de la tarea ImageNormalizer
// - n_images: número de imágenes a normalizar
// - intensity_max: intensidad máxima de la imagen
// - noisy_images_queue: Monitor tipo cola donde se van a obtener las imágenes con ruido
// - normalized_images_queue: Monitor tipo cola donde se van a añadir las imágenes normalizadas
ImageNormalizer::ImageNormalizer(int n_images, double intensity_max, ImageQueue &noisy_images_queue, ImageQueue &normalized_images_queue) : n_images(n_images), intensity_max(intensity_max), noisy_images_queue(noisy_images_queue), normalized_images_queue(normalized_images_queue){};

// Destructor de la tarea ImageNormalizer
ImageNormalizer::~ImageNormalizer(){};

// Método que calcula el mínimo de una imagen
// - image: imagen a calcular el mínimo
// - retorna el mínimo de la imagen
double ImageNormalizer::calculateMin(ImageContainer image)
{
    double min = image.image[0];
    for (int i = 1; i < image.size[0] * image.size[1]; i++)
    {
        if (image.image[i] < min)
        {
            min = image.image[i];
        }
    }
    return min;
};

// Método que normaliza una imagen
// - image: imagen a normalizar
// - retorna la imagen normalizada
ImageContainer ImageNormalizer::normalizeImage(ImageContainer image)
{
    double *normalized_image = new double[image.size[0] * image.size[1]];
    double *noised_image = image.image;
    double noised_min = calculateMin(image);

    // Se realiza la resta del mínimo de la imagen
    double min = noised_image[0] - noised_min;
    double max = noised_image[0] - noised_min;
    for (int i = 0; i < image.size[0] * image.size[1]; i++)
    {
        normalized_image[i] = noised_image[i] - noised_min;
        if (normalized_image[i] < min)
        {
            min = normalized_image[i];
        }
        if (normalized_image[i] > max)
        {
            max = normalized_image[i];
        }
    }

    // Se realiza la normalización de la imagen con la intensidad máxima
    double range = max - min;
    for (int i = 0; i < image.size[0] * image.size[1]; i++)
    {
        normalized_image[i] = normalized_image[i] * intensity_max / range;
    }

    image.image = normalized_image;
    delete[] noised_image;
    return image;
};

// Método principal de la tarea ImageNormalizer que normaliza las imágenes
// obtenidas del monitor noisy_images_queue y las añade al monitor normalized_images_queue
void ImageNormalizer::main()
{
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = noisy_images_queue.pop();
        ImageContainer normalized_image = normalizeImage(image);
        normalized_images_queue.push(normalized_image);
    }
};

#endif // IMAGE_NORMALIZER