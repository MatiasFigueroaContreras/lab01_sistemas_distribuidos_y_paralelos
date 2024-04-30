#ifndef IMAGE_WRITER
#define IMAGE_WRITER
#include "ImageWriter.h"
#include "fitsio.h"
#include <iostream>

ImageWriter::ImageWriter(int n_images, std::string prefix, ImageQueue &normalized_images_queue) : n_images(n_images), prefix(prefix), normalized_images_queue(normalized_images_queue){};

ImageWriter::~ImageWriter(){};

void ImageWriter::main()
{
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = normalized_images_queue.pop();
        std::cout << "Writing Image " << image.number << std::endl;
        std::string in_filename = prefix + std::to_string(image.number) + ".fits";
        std::string out_filename = prefix + "out" + std::to_string(image.number) + ".fits";
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
    }
};

#endif // IMAGE_WRITER