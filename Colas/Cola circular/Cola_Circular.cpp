#include <iostream>
using namespace std;

#define MAXSIZE 5
int queue[MAXSIZE];
int front = -1, rear = -1;

bool estaVacia() {
    return (front == -1);
}

bool estaLlena() {
    return ((rear + 1) % MAXSIZE == front);
}

void insertar() {
    int elemento;
    cout << "\nIngrese el elemento: ";
    cin >> elemento;

    if (estaLlena()) {
        cout << "\nDESBORDAMIENTO (OVERFLOW)\n";
        return;
    }

    if (estaVacia()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAXSIZE;
    }

    queue[rear] = elemento;
    cout << "\nElemento insertado correctamente.\n";
}

void eliminar() {
    if (estaVacia()) {
        cout << "\nSUBDESBORDAMIENTO (UNDERFLOW)\n";
        return;
    }

    int elemento = queue[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAXSIZE;
    }

    cout << "\nElemento eliminado: " << elemento << "\n";
}

void mostrar() {
    if (estaVacia()) {
        cout << "\nLa cola está vacía.\n";
        return;
    }

    cout << "\nElementos en la cola circular:\n";
    int i = front;
    while (true) {
        cout << queue[i] << " ";
        if (i == rear) break;
        i = (i + 1) % MAXSIZE;
    }
    cout << endl;
}

int main() {
    int opcion;
    do {
        cout << "\n*************** COLA CIRCULAR ***************\n";
        cout << "1. Insertar\n2. Eliminar\n3. Mostrar\n4. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertar(); break;
            case 2: eliminar(); break;
            case 3: mostrar(); break;
            case 4: cout << "\nSaliendo...\n"; break;
            default: cout << "\nOpción inválida.\n";
        }
    } while (opcion != 4);
    return 0;
}