//Eliminar Duplicados (10)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> arr = {5,3,8,3,5,1,9,8,2,5};

    cout << "Arreglo original: ";
    for(int n : arr) cout << n << " ";
    cout << endl;

    sort(arr.begin(), arr.end()); 
    arr.erase(unique(arr.begin(), arr.end()), arr.end()); 

    cout << "Arreglo sin duplicados: ";
    for(int n : arr) cout << n << " ";
    cout << endl;

    return 0;
}