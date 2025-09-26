#include <iostream>
using namespace std;

// Merge dos subarrays de a[].
void merge(int a[], int l, int m, int r) {
    int a1 = m - l + 1; // Tamaño del primer subarray
    int a2 = r - m;     // Tamaño del segundo subarray

    // Crear arrays temporales
    int* L = new int[a1]; // Crear array temporal
    int* R = new int[a2]; // Crear array temporal

    // Copiar datos a los arrays temporales L[] y R[]
    for (int j = 0; j < a1; j++) // copiar datos al array temporal
        L[j] = a[l + j];
    for (int k = 0; k < a2; k++) // copiar datos al array temporal
        R[k] = a[m + 1 + k];

    int i = 0; // Indice inicial del primer subarray
    int j = 0; // Indice inicial del segundo subarray
    int k = l; // Indice inicial del subarray mezclado

    // Mezclar los arrays temporales de nuevo en a[l..r]
    while (i < a1 && j < a2) { // recorrer ambos arrays
        if (L[i] <= R[j]) {    // comparar los elementos de ambos arrays
            a[k] = L[i];       // copiar el elemento más pequeño al array original
            i = i + 1;         // incrementar el índice del primer array
        } else {               // si el elemento del segundo array es más pequeño
            a[k] = R[j];       // copiar el elemento más pequeño al array original
            j = j + 1;         // incrementar el índice del segundo array
        }
        k = k + 1;             // incrementar el índice del array original
    }

    // copiar los elementos restantes de L[], si hay alguno
    while (i < a1) { // copiar los elementos restantes del primer array
        a[k] = L[i]; // copiar el elemento al array original
        i = i + 1;   // incrementar el índice del primer array
        k = k + 1;   // incrementar el índice del array original
    }

    // copiar los elementos restantes de R[], si hay alguno
    while (j < a2) { // copiar los elementos restantes del segundo array
        a[k] = R[j]; // copiar el elemento al array original
        j = j + 1;   // incrementar el índice del segundo array
        k = k + 1;   // incrementar el índice del array original
    }

    delete[] L;
    delete[] R;
}

// función principal que ordena a[l..r]
void mergeSort(int a[], int l, int r) {
    if (l < r) {
        // Igual que (l + r)//2, pero evita el desbordamiento
        int m = l + (r - l) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(a, l, m);     // ordenar la primera mitad
        mergeSort(a, m + 1, r); // ordenar la segunda mitad
        merge(a, l, m, r);      // mezclar las dos mitades
    }
}

// Código para probar la implementación de MergeSort
int main() {
    int a[] = {39, 28, 44, 11}; // arreglo desordenado
    int s = sizeof(a) / sizeof(a[0]); // tamaño del arreglo

    cout << "Antes de ordenar el arreglo: ";
    for (int j = 0; j < s; j++)
        cout << a[j] << " ";

    mergeSort(a, 0, s - 1); // llama a la función mergeSort

    cout << "\nDespués de ordenar el arreglo: ";
    for (int j = 0; j < s; j++)
        cout << a[j] << " ";

    return 0;
}