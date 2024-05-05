#ifndef IMAGE_READER_H
#define IMAGE_READER_H
#include <string>
#include "ImageQueue.h"

// Tarea para leer imágenes y añadirlas a la cola de imágenes
// - n_images: número de imágenes a leer
// - prefix: prefijo del nombre de las imágenes a leer
// - images_queue: Monitor tipo cola donde se van a añadir las imágenes leídas
_Task ImageReader
{
    int n_images;
    std::string prefix;
    ImageQueue & images_queue;

public:
    ImageReader(int n_images, std::string prefix, ImageQueue &images_queue);
    ~ImageReader();

private:
    ImageContainer read_image(int i);
    void main();
};

#endif // IMAGE_READER_H|