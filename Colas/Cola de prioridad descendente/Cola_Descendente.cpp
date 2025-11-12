#include <iostream>
using namespace std;

#define MAXSIZE 5
int queue[MAXSIZE];
int count = 0;

void insertar() {
    if (count == MAXSIZE) {
        cout << "\nDESBORDAMIENTO (OVERFLOW)\n";
        return;
    }

    int elemento;
    cout << "\nIngrese el elemento: ";
    cin >> elemento;

    int i = count - 1;
    while (i >= 0 && queue[i] < elemento) {
        queue[i + 1] = queue[i];
        i--;
    }
    queue[i + 1] = elemento;
    count++;

    cout << "\nElemento insertado correctamente.\n";
}

void eliminar() {
    if (count == 0) {
        cout << "\nSUBDESBORDAMIENTO (UNDERFLOW)\n";
        return;
    }

    cout << "\nElemento eliminado (mayor prioridad): " << queue[0] << "\n";
    for (int i = 1; i < count; i++) {
        queue[i - 1] = queue[i];
    }
    count--;
}

void mostrar() {
    if (count == 0) {
        cout << "\nLa cola está vacía.\n";
        return;
    }

    cout << "\nElementos (orden descendente):\n";
    for (int i = 0; i < count; i++)
        cout << queue[i] << " ";
    cout << endl;
}

int main() {
    int opcion;
    do {
        cout << "\n******** COLA DE PRIORIDAD DESCENDENTE ********\n";
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