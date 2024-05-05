#ifndef IMAGE_WRITER
#define IMAGE_WRITER
#include "ImageWriter.h"
#include "fitsio.h"
#include <iostream>

// Constructor de la tarea ImageWriter
// - n_images: número de imágenes a escribir
// - input_prefix: prefijo de las imágenes de entrada
// - output_prefix: prefijo de las imágenes de salida
// - normalized_images_queue: Monitor tipo cola donde se van a obtener las imágenes normalizadas
ImageWriter::ImageWriter(int n_images, std::string input_prefix, std::string output_prefix, ImageQueue &normalized_images_queue) : n_images(n_images), input_prefix(input_prefix), output_prefix(output_prefix), normalized_images_queue(normalized_images_queue){};

// Destructor de la tarea ImageWriter
ImageWriter::~ImageWriter(){};

// Método para escribir una imagen
// - image: imagen a escribir
void ImageWriter::writeImage(ImageContainer image)
{
    std::string in_filename = input_prefix + std::to_string(image.number) + ".fits";
    std::string out_filename = output_prefix + std::to_string(image.number) + ".fits";
    fitsfile *in_fptr;
    fitsfile *out_fptr;
    int status = 0;
    long fpixel = 1;
    fits_open_file(&in_fptr, in_filename.c_str(), READONLY, &status);
    fits_create_file(&out_fptr, out_filename.c_str(), &status);
    fits_copy_header(in_fptr, out_fptr, &status);
    fits_write_img(out_fptr, TDOUBLE, fpixel, image.size[0] * image.size[1], image.image, &status);
    fits_close_file(in_fptr, &status);
    fits_close_file(out_fptr, &status);
    delete[] image.image;
};

// Método donde se ejecuta la hebra de la tarea ImageWriter
//  esta escribe las imágenes normalizadas obtenidas del 
//  monitor normalized_images_queue
void ImageWriter::main()
{
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = normalized_images_queue.pop();
        writeImage(image);
    }
};

#endif // IMAGE_WRITER