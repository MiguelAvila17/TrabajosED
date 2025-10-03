//Ordenar Filas (3x3)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<vector<int>> mat = {
        {9, 2, 7},
        {3, 6, 1},
        {4, 8, 5}
    };

    cout << "Matriz original:\n";
    for(auto& fila : mat) {
        for(int n : fila) cout << n << " ";
        cout << endl;
    }

    for(auto& fila : mat) sort(fila.begin(), fila.end());

    cout << "\nMatriz con filas ordenadas:\n";
    for(auto& fila : mat) {
        for(int n : fila) cout << n << " ";
        cout << endl;
    }

    return 0;
}