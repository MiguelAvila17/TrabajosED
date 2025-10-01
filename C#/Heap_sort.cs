using System;

class HeapSort {
    // Ajustar un subárbol al heap máximo
    static void Heapify(int[] arr, int n, int i) {
        int largest = i;          
        int left = 2 * i + 1;     
        int right = 2 * i + 2;    

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            Heapify(arr, n, largest);
        }
    }

    // Heapsort
    public static void Sort(int[] arr) {
        int n = arr.Length;

        // Construir heap máximo
        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(arr, n, i);

        // Extraer elementos
        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            Heapify(arr, i, 0);
        }
    }

    static void Main(string[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};
        
        Console.WriteLine("Antes de ordenar: " + string.Join(", ", arr));
        Sort(arr);
        Console.WriteLine("Después de ordenar: " + string.Join(", ", arr));
    }
}