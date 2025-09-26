#include <iostream>
using namespace std;

// Función para intercambiar dos elementos en el arreglo 
void swap(int &a, int &b) { // intercambia los elementos
    int temp = a;
    a = b;
    b = temp;
}

// Función para hacer la partición del arreglo 
int partition(int a[], int l, int h) {
    // Selecciona el elemento pivote
    int pvt = a[h];
    // j es el índice de los elementos que son menores que 
    // pivot y también indica la posición correcta del pivot encontrado hasta este momento
    int j = l - 1;
    // Recorre a[l..h-1] y mueve todos los elementos menores
    // al lado izquierdo del pivote.
    for (int k = l; k < h; k++) { // recorre el arreglo
        // Si el elemento actual es menor que el pivote
        if (a[k] < pvt) { // compara el elemento actual con el pivote 
            j++; // incrementa el índice del elemento más pequeño 
            swap(a[j], a[k]); // intercambia los elementos
        }
    }
    // Mover el pivote después de elementos más pequeños y devolverlo a su posición
    swap(a[j + 1], a[h]); // intercambia el pivote con el elemento siguiente al último elemento más pequeño
    return j + 1; // devuelve el índice del pivote
}

// Implementación de la función QuickSort 
void qckSort(int a[], int l, int h) { // función principal de QuickSort
    if (l < h) { // si el índice izquierdo es menor que el derecho
        int pi = partition(a, l, h); // particiona el arreglo
        qckSort(a, l, pi - 1); // llamada recursiva para los elementos menores que el pivote 
        qckSort(a, pi + 1, h); // llamada recursiva para los elementos mayores o iguales que el pivote
    }
}

int main() { // punto de entrada del programa
    int a[] = {10, 7, 8, 9, 1, 5}; // arreglo desordenado
    int size = sizeof(a) / sizeof(a[0]); // tamaño del arreglo

    cout << "El arreglo antes de ordenarlo:\n";
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    cout << "\n";

    qckSort(a, 0, size - 1);

    cout << "El arreglo después de ordenarlo:\n";
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    return 0;
}