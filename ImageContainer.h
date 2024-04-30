#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

struct ImageContainer
{
    double *image;
    long size[2];
    int number;
};

#endif // IMAGECONTAINER_H