using System;

class QuickSort {
    // Función para intercambiar dos elementos en el arreglo 
    static void Swap(int[] a, int j, int k) { // intercambia los elementos
        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
    }

    // Función para hacer la partición del arreglo 
    static int Partition(int[] a, int l, int h) {
        // Selecciona el elemento pivote
        int pvt = a[h];
        // j es el índice de los elementos que son menores que el pivote
        int j = l - 1;
        // Recorre a[l..h-1] y mueve todos los elementos menores al lado izquierdo del pivote.
        for (int k = l; k < h; k++) {
            // Si el elemento actual es menor que el pivote
            if (a[k] < pvt) {
                j++; // incrementa el índice del elemento más pequeño
                Swap(a, j, k); // intercambia los elementos
            }
        }
        // Mover el pivote después de elementos más pequeños y devolverlo a su posición
        Swap(a, j + 1, h);
        return j + 1;
    }

    // Implementación de la función QuickSort 
    static void QckSort(int[] a, int l, int h) {
        if (l < h) {
            int pi = Partition(a, l, h);
            QckSort(a, l, pi - 1);
            QckSort(a, pi + 1, h);
        }
    }

    static void Main() {
        int[] a = { 10, 7, 8, 9, 1, 5 }; // arreglo desordenado
        int size = a.Length;

        Console.WriteLine("El arreglo antes de ordenarlo:");
        foreach (int v in a) Console.Write(v + " ");
        Console.WriteLine();

        QckSort(a, 0, size - 1);

        Console.WriteLine("El arreglo después de ordenarlo:");
        foreach (int v in a) Console.Write(v + " ");
    }
}