#include <iostream>
#include "ImageQueue.h"
#include "ImageReader.h"
#include "ImageSmoother.h"
#include "GaussianNoiseInjector.h"
#include "ImageNormalizer.h"
#include "ImageWriter.h"
#include <cstdlib>
#include <uC++.h>

// Clase que representa el pipeline de procesamiento de imágenes
// se encarga de instanciar las tareas y monitores necesarios
// para que las imágenes sean leídas, suavizadas, inyectadas con ruido
// normalizadas y escritas, por sus respectivas tareas.
int main(int argc, char *argv[])
{
    // Se obtienen los argumentos de la línea de comandos
    int opt;
    int N;
    std::string input_prefix, output_prefix;
    float theta_fraction;
    double std_dev;
    double intensity_max;
    while ((opt = getopt(argc, argv, "i:o:s:t:j:N:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            input_prefix = optarg;
            break;
        case 'o':
            output_prefix = optarg;
            break;
        case 's':
            std_dev = atof(optarg);
            break;
        case 't':
            theta_fraction = atof(optarg);
            break;
        case 'j':
            intensity_max = atof(optarg);
            break;
        case 'N':
            N = atoi(optarg);
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " -i [image input prefix] -o [image output prefix] -s [standard deviation] -t [theta fraction] -j [max intensity] -N [number of images]" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Se instancian las tareas y monitores necesarios
    ImageQueue images_queue(N);
    ImageReader read_images(N, input_prefix, images_queue);
    ImageQueue smoothed_images_queue(N);
    ImageSmoother images_smoother(N, theta_fraction, images_queue, smoothed_images_queue);
    ImageQueue noisy_images_queue(N);
    GaussianNoiseInjector gaussian_noise_injector(N, std_dev, smoothed_images_queue, noisy_images_queue);
    ImageQueue normalized_images_queue(N);
    ImageNormalizer image_normalizer(N, intensity_max, noisy_images_queue, normalized_images_queue);
    ImageWriter write_images(N, input_prefix, output_prefix, normalized_images_queue);

    return 0;
};