#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<double>& bukt) {
    for (size_t j = 1; j < bukt.size(); j++) {
        double val = bukt[j];
        int k = j - 1;
        while (k >= 0 && bukt[k] > val) {
            bukt[k + 1] = bukt[k];
            k--;
        }
        bukt[k + 1] = val;
    }
}

void bucketSort(vector<double>& arr) {
    int s = arr.size();
    vector<vector<double>> buckets(s);

    for (double num : arr) {
        int bi = int(s * num);
        if (bi >= s) bi = s - 1;
        buckets[bi].push_back(num);
    }

    for (auto& b : buckets) {
        insertionSort(b);
    }

    int idx = 0;
    for (auto& b : buckets) {
        for (double num : b) {
            arr[idx++] = num;
        }
    }
}

int main() {
    vector<double> inputArr = {0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67};
    cout << "Arreglo antes de ordenar:\n";
    for (double x : inputArr) cout << x << " ";
    cout << endl;

    bucketSort(inputArr);

    cout << "Arreglo después de ordenar:\n";
    for (double x : inputArr) cout << x << " ";
    cout << endl;
}