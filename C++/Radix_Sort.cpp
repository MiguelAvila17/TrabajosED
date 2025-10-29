#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int n = arr.size();

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        vector<int> output(n);
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int index = (arr[i] / exp) % 10;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr);
    cout << "Arreglo ordenado: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
}