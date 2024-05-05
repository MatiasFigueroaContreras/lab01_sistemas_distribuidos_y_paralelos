#ifndef IMAGE_READER
#define IMAGE_READER
#include "ImageReader.h"
#include <iostream>
#include "fitsio.h"

// Constructor de la tarea ImageReader
// - n_images: número de imágenes a leer
// - prefix: prefijo del nombre de las imágenes a leer
// - images_queue: Monitor tipo cola donde se van a añadir las imágenes leídas
ImageReader::ImageReader(int n_images, std::string prefix, ImageQueue &images_queue) : n_images(n_images), prefix(prefix), images_queue(images_queue){};

// Destructor de la tarea ImageReader
ImageReader::~ImageReader(){

};

// Método para leer una imagen
// - i: número de la imagen a leer
// - retorna la imagen leída
ImageContainer ImageReader::read_image(int i)
{
    ImageContainer image;
    image.number = i;
    fitsfile *fptr;
    int status = 0;
    long size[2];
    double *rimage;
    std::string filename = prefix + std::to_string(i) + ".fits";
    fits_open_file(&fptr, filename.c_str(), READONLY, &status);
    fits_get_img_size(fptr, 2, size, &status);
    rimage = new double[size[0] * size[1]];
    fits_read_img(fptr, TDOUBLE, 1, size[0] * size[1], NULL, rimage, NULL, &status);
    image.image = rimage;
    image.size[0] = size[0];
    image.size[1] = size[1];
    fits_close_file(fptr, &status);
    return image;
};

// Método donde se ejecuta la hebra de la tarea ImageReader
//  esta lee las imágenes y las añade al monitor images_queue
void ImageReader::main()
{
    for (int i = 1; i <= n_images; i++)
    {
        ImageContainer image = read_image(i);
        images_queue.push(image);
    };
}

#endif // IMAGE_READER
