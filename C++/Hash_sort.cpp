#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void hashSort(vector<int>& arr) {
    unordered_map<int, int> hashTable;
    int maxVal = 0;

    for (int num : arr) {
        hashTable[num]++;
        if (num > maxVal) maxVal = num;
    }

    arr.clear();
    for (int i = 0; i <= maxVal; i++) {
        if (hashTable.find(i) != hashTable.end()) {
            for (int j = 0; j < hashTable[i]; j++) {
                arr.push_back(i);
            }
        }
    }
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    cout << "Arreglo original: ";
    for (int n : arr) cout << n << " ";
    cout << endl;

    hashSort(arr);

    cout << "Arreglo ordenado: ";
    for (int n : arr) cout << n << " ";
}