// Nodo.h
#ifndef NODO_H
#define NODO_H

struct Nodo {
    int clave;
    Nodo *izquierda;
    Nodo *derecha;

    // Constructor
    Nodo(int k) : clave(k), izquierda(nullptr), derecha(nullptr) {}
};

#endif // NODO_H