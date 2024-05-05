#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

// Estructura para guardar los datos de una imagen
// - image: contiene la imagen
// - size: contiene el tamaño de la imagen
// - number: contiene el número de la imagen
struct ImageContainer
{
    double *image;
    long size[2];
    int number;
};

#endif // IMAGECONTAINER_H