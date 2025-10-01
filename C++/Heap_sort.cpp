#include <iostream>
using namespace std;

// Función para ajustar un subárbol al heap máximo
void heapify(int arr[], int n, int i) {
    int largest = i;          // Inicialmente, asumimos que la raíz es el mayor
    int left = 2 * i + 1;     // Hijo izquierdo
    int right = 2 * i + 2;    // Hijo derecho

    // Si el hijo izquierdo es mayor que la raíz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es mayor que el mayor actual
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el mayor no es la raíz
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Implementación de Heapsort
void heapsort(int arr[], int n) {
    // Construir heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos uno a uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Mover raíz al final
        heapify(arr, i, 0);   // Heapify en el heap reducido
    }
}

// Programa principal
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Antes de ordenar: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapsort(arr, n);

    cout << "Después de ordenar: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}