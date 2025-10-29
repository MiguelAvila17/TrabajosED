#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
using namespace std;
using namespace std::chrono;

// ----------------- ALGORITMOS -----------------

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

int partitionQS(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Hash sort (simplificado, usando hash directo)
void hashSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> hashTable(maxVal + 1, 0);
    for (int val : arr) hashTable[val]++;
    arr.clear();
    for (int i = 0; i <= maxVal; i++)
        for (int j = 0; j < hashTable[i]; j++)
            arr.push_back(i);
}

// Bucket Sort (para datos pequeños)
void bucketSort(vector<int>& arr) {
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> bucket(maxVal + 1, 0);
    for (int val : arr) bucket[val]++;
    arr.clear();
    for (int i = 0; i <= maxVal; i++)
        for (int j = 0; j < bucket[i]; j++)
            arr.push_back(i);
}

// Radix Sort
int getMax(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n), count(10, 0);
    for (int i = 0; i < n; i++) count[(arr[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10] - 1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int m = getMax(arr);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, exp);
}

// ----------------- UTILIDADES -----------------

void generarArreglo(vector<int>& arr, int n, int tipo) {
    arr.resize(n);
    random_device rd; mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n);
    for (int i = 0; i < n; i++) arr[i] = dis(gen);
    if (tipo == 1) sort(arr.begin(), arr.end());
    else if (tipo == 2) reverse(arr.begin(), arr.end());
}

double medirTiempo(void (*func)(vector<int>&), vector<int> arr) {
    auto inicio = high_resolution_clock::now();
    func(arr);
    auto fin = high_resolution_clock::now();
    return duration<double, milli>(fin - inicio).count();
}

// ----------------- MAIN -----------------

int main() {
    vector<int> tamanos = {100, 1000, 10000};
    vector<string> tipos = {"Aleatorio", "Ordenado", "Inverso"};

    ofstream archivo("resultados.csv");
    archivo << "Algoritmo,Tamano,Tipo,Tiempo(ms)\n";

    vector<pair<string, void(*)(vector<int>&)>> algoritmos = {
        {"Bubble Sort", bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Quick Sort", [](vector<int>& a){quickSort(a,0,a.size()-1);}},
        {"Merge Sort", [](vector<int>& a){mergeSort(a,0,a.size()-1);}},
        {"Heap Sort", heapSort},
        {"Hash Sort", hashSort},
        {"Bucket Sort", bucketSort},
        {"Radix Sort", radixSort}
    };

    for (int n : tamanos) {
        for (int t = 0; t < 3; t++) {
            vector<int> base;
            generarArreglo(base, n, t);
            for (auto& alg : algoritmos) {
                double tiempo = medirTiempo(alg.second, base);
                archivo << alg.first << "," << n << "," << tipos[t] << "," << tiempo << "\n";
                cout << alg.first << " (" << tipos[t] << ", n=" << n << "): " << tiempo << " ms\n";
            }
        }
    }

    archivo.close();
    cout << "\nResultados guardados en 'resultados.csv'.\n";
    return 0;
}