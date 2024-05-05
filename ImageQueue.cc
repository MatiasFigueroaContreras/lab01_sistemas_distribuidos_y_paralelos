#ifndef IMAGE_QUEUE
#define IMAGE_QUEUE
#include "ImageQueue.h"

// Constructor de la cola de imágenes
// - n_images: número maximo de imágenes que se van a guardar en la cola
ImageQueue::ImageQueue(int n_images) {
    front = 0;
    back = 0;
    count = 0;
    queue = new ImageContainer[n_images];
};

// Destructor de la cola de imágenes
ImageQueue::~ImageQueue() {
    delete[] queue;
};

// Método para agregar una imagen a la cola
// - image: imagen a agregar
void ImageQueue::push(ImageContainer image) {
    queue[back] = image;
    back++;
    count++;
    // Se desbloquea una hebra que esté esperando a que la cola no esté vacía
    not_empty.signal();
};

// Método para sacar una imagen de la cola
// - retorna la imagen sacada de la cola
ImageContainer ImageQueue::pop() {
    // Si la cola está vacía se bloquea la hebra, hasta que se añada una imagen
    if(count == 0) not_empty.wait(); 
    ImageContainer image = queue[front];
    front++;
    count--;
    return image;
};

#endif // IMAGE_QUEUE