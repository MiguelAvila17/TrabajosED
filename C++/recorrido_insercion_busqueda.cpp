#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {10, 20, 30, 40, 50};

    // 1. Recorrido
    cout << "Recorrido del arreglo:" << endl;
    for (int v : arr) {
        cout << v << endl;
    }

    // 2. Insertar en índice
    arr.insert(arr.begin() + 2, 99);
    cout << "Después de insertar: ";
    for (int v : arr) cout << v << " ";
    cout << endl;

    // 3. Búsqueda lineal
    int x = 30;
    bool encontrado = false;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == x) {
            cout << "Elemento " << x << " encontrado en índice " << i << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
        cout << "Elemento " << x << " no encontrado" << endl;

    return 0;
}
