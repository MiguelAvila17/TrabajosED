#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void selection(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int small = i;
        for (int j = i + 1; j < n; j++) {
            if (a[small] > a[j]) {
                small = j;
            }
        }
        swap(a[i], a[small]);
    }
}

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int n = 5;
    int a[5];

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100 + 1;
    }

    cout << "Arreglo antes de ser ordenado:\n";
    printArr(a, n);

    selection(a, n);

    cout << "\nArreglo después de ser ordenado:\n";
    printArr(a, n);

    return 0;
}