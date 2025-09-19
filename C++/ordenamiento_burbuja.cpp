#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int N = 10;
    int arr[N];

    // Inicializar la semilla de números aleatorios
    srand(time(0));

    // Llenar arreglo con números aleatorios entre 1 y 100
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100 + 1;
    }

    cout << "Original: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    burbuja(arr, N);

    cout << "Ordenado: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}