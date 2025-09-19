#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    srand(time(0));
    vector<int> arr;
    for (int i = 0; i < 10; i++) arr.push_back(rand() % 100 + 1);

    cout << "Antes de ordenar: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    insertionSort(arr);

    cout << "Después de ordenar: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}