#ifndef IMAGE_NORMALIZER_H
#define IMAGE_NORMALIZER_H
#include "ImageQueue.h"

// Tarea encargada de normalizar las imágenes
// - n_images: número de imágenes a normalizar
// - intensity_max: intensidad máxima en mili Janskys de la imagen
// - noisy_images_queue: Monitor tipo cola donde se van a obtener las imágenes con ruido
// - normalized_images_queue: Monitor tipo cola donde se van a añadir las imágenes normalizadas
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
    double calculateMin(ImageContainer image);
    ImageContainer normalizeImage(ImageContainer image);
    void main();
};

#endif // IMAGE_NORMALIZER_H