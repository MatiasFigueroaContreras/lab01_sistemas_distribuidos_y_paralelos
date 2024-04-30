#ifndef IMAGE_SMOOTHER
#define IMAGE_SMOOTHER
#include "ImageSmoother.h"
#include <cmath>
#include <iostream>

ImageSmoother::ImageSmoother(int n_images, float theta_fraction, ImageQueue &images_queue, ImageQueue &smoothed_images_queue)
    : n_images(n_images), theta_fraction(theta_fraction), images_queue(images_queue), smoothed_images_queue(smoothed_images_queue)
{
};

ImageSmoother::~ImageSmoother()
{
};

double **ImageSmoother::calcKernel()
{
    float sigma_x = 3.5;
    float sigma_y = 3.5;
    double a = std::pow(std::cos(theta_fraction), 2) / (2 * std::pow(sigma_x, 2)) + std::pow(std::sin(theta_fraction), 2) / (2 * std::pow(sigma_y, 2));
    double b = std::pow(std::sin(2 * theta_fraction), 2) / (4 * std::pow(sigma_x, 2)) + std::pow(std::sin(2.0 * theta_fraction), 2) / (4 * std::pow(sigma_y, 2));
    double c = std::pow(std::sin(theta_fraction), 2) / (2 * std::pow(sigma_x, 2)) + std::pow(std::cos(theta_fraction), 2) / (2 * std::pow(sigma_y, 2));
    int x_0 = 13;
    int y_0 = 13;
    double **kernel = new double *[27];
    for (int i = 0; i < 27; i++)
    {
        kernel[i] = new double[27];
    }

    double sum = 0;
    for (int x = 0; x < 27; x++)
    {
        for (int y = 0; y < 27; y++)
        {
            kernel[x][y] = std::exp(-(a * std::pow((x - x_0), 2) - 2 * b * (x - x_0) * (y - y_0) + c * std::pow((y - y_0), 2)));
            sum += kernel[x][y];
        }
    }

    // Se aplica la normalizacion
    for (int x = 0; x < 27; x++)
    {
        for (int y = 0; y < 27; y++)
        {
            kernel[x][y] /= sum;
        }
    }
    return kernel;
};

double *ImageSmoother::convolveImage(ImageContainer image, double **kernel)
{
    double normalization_factor = (9.925 * std::pow(10, -11)) / (1.186 * std::pow(10, -12));
    double *smoothed_image = new double[image.size[0] * image.size[1]];
    for (int x = 0; x < image.size[0]; x++)
    {
        for (int y = 0; y < image.size[1]; y++)
        {
            int location = x * image.size[1] + y;
            smoothed_image[location] = 0;
            for (int i = 0; i < 27; i++)
            {
                for (int j = 0; j < 27; j++)
                {
                    int x_k = x + i - 13;
                    int y_k = y + j - 13;
                    if (x_k >= 0 && x_k < image.size[0] && y_k >= 0 && y_k < image.size[1])
                    {
                        smoothed_image[location] += image.image[x_k * image.size[1] + y_k] * kernel[i][j];
                    }
                }
            }
            smoothed_image[location] *= normalization_factor; // Normalizacion
        }
    }
    return smoothed_image;
};

void ImageSmoother::main()
{
    double **kernel = calcKernel();
    for (int i = 0; i < n_images; i++)
    {
        ImageContainer image = images_queue.pop();
        std::cout << "Smoothing image " << image.number << " Size: [" << image.size[0] << ", " << image.size[1] << "]" << std::endl;
        double *smoothed_image = convolveImage(image, kernel);
        delete image.image;
        image.image = smoothed_image;
        smoothed_images_queue.push(image);
    }

    for (int i = 0; i < 27; i++)
    {
        delete[] kernel[i];
    }
    delete[] kernel;
};

#endif // IMAGES_SMOOTHER