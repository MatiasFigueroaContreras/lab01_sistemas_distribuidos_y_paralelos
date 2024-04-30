#ifndef IMAGE_NORMALIZER
#define IMAGE_NORMALIZER
#include "ImageNormalizer.h"
#include <iostream>

ImageNormalizer::ImageNormalizer(int n_images, double intensity_max, ImageQueue &noisy_images_queue, ImageQueue &normalized_images_queue) : n_images(n_images), intensity_max(intensity_max), noisy_images_queue(noisy_images_queue), normalized_images_queue(normalized_images_queue){};

ImageNormalizer::~ImageNormalizer(){};

void ImageNormalizer::main()
{
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = noisy_images_queue.pop();
        std::cout << "Normalizing Image " << image.number << std::endl;
        double *normalized_image = new double[image.size[0] * image.size[1]];
        double *noised_image = image.image;
        double noised_min = noised_image[0];
        for (int i = 0; i < image.size[0] * image.size[1]; i++)
        {
            if (noised_image[i] < noised_min)
            {
                noised_min = noised_image[i];
            }
        }

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

        for (int i = 0; i < image.size[0] * image.size[1]; i++)
        {
            normalized_image[i] = normalized_image[i] * intensity_max / (max - min);
        }

        image.image = normalized_image;
        normalized_images_queue.push(image);
        delete[] noised_image;
    }
};

#endif // IMAGE_NORMALIZER