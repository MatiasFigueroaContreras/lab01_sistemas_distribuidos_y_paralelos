#ifndef IMAGE_SMOOTHER_H
#define IMAGE_SMOOTHER_H
#include "ImageQueue.h"

// Tarea para suavizar imágenes mediante la convolución con un kernel 
//  y añadirlas a la cola de imágenes suavizadas
// - n_images: número de imágenes a suavizar
// - theta_fraction: fracción de la imagen que se va a suavizar
// - images_queue: Monitor tipo cola donde se van a obtener las imágenes a suavizar
// - smoothed_images_queue: Monitor tipo cola donde se van a añadir las imágenes suavizadas
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