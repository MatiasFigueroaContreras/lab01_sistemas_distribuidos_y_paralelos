#ifndef IMAGE_QUEUE_H
#define IMAGE_QUEUE_H
#include "ImageContainer.h"

// Clase Monitor para la cola de imágenes
// - front: índice del primer elemento
// - back: índice del último elemento
// - count: número de elementos en la cola
// - not_empty: variable de condición para bloquear el uso de la 
//              cola si está vacía
_Monitor ImageQueue
{
    int front, back, count;
    uCondition not_empty;
    ImageContainer *queue;

public:
    ImageQueue(int n_images);
    ~ImageQueue();
    void push(ImageContainer image);
    ImageContainer pop();
};

#endif // IMAGE_QUEUE_H
