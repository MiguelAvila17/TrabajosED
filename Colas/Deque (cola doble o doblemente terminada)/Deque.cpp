#include <iostream>
using namespace std;

#define MAXSIZE 5
int dequeArr[MAXSIZE];
int front = -1, rear = -1;

bool estaVacia() {
    return (front == -1);
}

bool estaLlena() {
    return ((front == 0 && rear == MAXSIZE - 1) || (front == rear + 1));
}

void insertarFrente() {
    if (estaLlena()) {
        cout << "\nDESBORDAMIENTO (OVERFLOW)\n";
        return;
    }
    int elemento;
    cout << "\nIngrese el elemento: ";
    cin >> elemento;

    if (front == -1) { // primer elemento
        front = rear = 0;
    } else if (front == 0) {
        front = MAXSIZE - 1;
    } else {
        front--;
    }

    dequeArr[front] = elemento;
    cout << "\nElemento insertado al frente.\n";
}

void insertarFinal() {
    if (estaLlena()) {
        cout << "\nDESBORDAMIENTO (OVERFLOW)\n";
        return;
    }
    int elemento;
    cout << "\nIngrese el elemento: ";
    cin >> elemento;

    if (rear == -1) { // primer elemento
        front = rear = 0;
    } else if (rear == MAXSIZE - 1) {
        rear = 0;
    } else {
        rear++;
    }

    dequeArr[rear] = elemento;
    cout << "\nElemento insertado al final.\n";
}

void eliminarFrente() {
    if (estaVacia()) {
        cout << "\nSUBDESBORDAMIENTO (UNDERFLOW)\n";
        return;
    }

    cout << "\nElemento eliminado del frente: " << dequeArr[front] << "\n";

    if (front == rear) { // solo un elemento
        front = rear = -1;
    } else if (front == MAXSIZE - 1) {
        front = 0;
    } else {
        front++;
    }
}

void eliminarFinal() {
    if (estaVacia()) {
        cout << "\nSUBDESBORDAMIENTO (UNDERFLOW)\n";
        return;
    }

    cout << "\nElemento eliminado del final: " << dequeArr[rear] << "\n";

    if (front == rear) { // solo un elemento
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAXSIZE - 1;
    } else {
        rear--;
    }
}

void mostrar() {
    if (estaVacia()) {
        cout << "\nEl deque está vacío.\n";
        return;
    }

    cout << "\nElementos en el deque:\n";
    int i = front;
    while (true) {
        cout << dequeArr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % MAXSIZE;
    }
    cout << endl;
}

int main() {
    int opcion;
    do {
        cout << "\n*************** DEQUE (COLA DOBLE) ***************\n";
        cout << "1. Insertar al frente\n";
        cout << "2. Insertar al final\n";
        cout << "3. Eliminar del frente\n";
        cout << "4. Eliminar del final\n";
        cout << "5. Mostrar\n";
        cout << "6. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertarFrente(); break;
            case 2: insertarFinal(); break;
            case 3: eliminarFrente(); break;
            case 4: eliminarFinal(); break;
            case 5: mostrar(); break;
            case 6: cout << "\nSaliendo...\n"; break;
            default: cout << "\nOpción inválida.\n";
        }
    } while (opcion != 6);

    return 0;
}