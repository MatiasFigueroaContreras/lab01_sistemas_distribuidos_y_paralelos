#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H
#include "ImageQueue.h"
#include <string>

// Tarea encargada de escribir las imágenes normalizadas
// - n_images: número de imágenes a escribir
// - input_prefix: prefijo de las imágenes de entrada
// - output_prefix: prefijo de las imágenes de salida
// - normalized_images_queue: Monitor tipo cola donde se van a obtener las imágenes normalizadas
_Task ImageWriter
{
    int n_images;
    std::string input_prefix;
    std::string output_prefix;
    ImageQueue & normalized_images_queue;

public:
    ImageWriter(int n_images, std::string input_prefix, std::string output_prefix, ImageQueue &normalized_images_queue);
    ~ImageWriter();

private:
    void writeImage(ImageContainer image);
    void main();
};

#endif // IMAGE_WRITER_H