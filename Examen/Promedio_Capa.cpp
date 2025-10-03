//Promedio x Capa (3x3x3)

#include <iostream>
#include <vector>

using namespace std;
//Agregar ciclos

int main() {
    vector<vector<vector<int>>> arr3D = {
        { {1,2,3}, {4,5,6}, {7,8,9} },
        { {10,11,12}, {13,14,15}, {16,17,18} },
        { {19,20,21}, {22,23,24}, {25,26,27} }
    };

    for(int capa = 0; capa < arr3D.size(); capa++) {
        double suma = 0;
        int cont = 0;
        for(auto& fila : arr3D[capa]) {
            for(int val : fila) {
                suma += val;
                cont++;
            }
        }
        double promedio = suma / cont;
        cout << "Promedio de la capa " << capa+1 << ": " << promedio << endl;
    }

    return 0;
}