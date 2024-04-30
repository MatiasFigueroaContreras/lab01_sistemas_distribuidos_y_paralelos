#ifndef IMAGE_READER
#define IMAGE_READER
#include "ImageReader.h"
#include <iostream>
#include "fitsio.h"

ImageReader::ImageReader(int n_images, std::string prefix, ImageQueue &images_queue) : n_images(n_images), prefix(prefix), images_queue(images_queue){};

ImageReader::~ImageReader(){

};

void ImageReader::main()
{
    for (int i = 1; i <= n_images; i++)
    {
        std::cout << "Reading image " << i << std::endl;
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
        images_queue.push(image);
        fits_close_file(fptr, &status);
    };
}

#endif // IMAGE_READER
