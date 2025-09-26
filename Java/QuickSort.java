public class QuickSort {
    // Función para intercambiar dos elementos en el arreglo 
    static void swap(int[] a, int j, int k) { // intercambia los elementos
        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
    }

    // Función para hacer la partición del arreglo 
    static int partition(int[] a, int l, int h) {
        int pvt = a[h]; // Selecciona el elemento pivote
        int j = l - 1;  // índice de los elementos menores
        for (int k = l; k < h; k++) { // recorre el arreglo
            if (a[k] < pvt) { // Si el elemento actual es menor que el pivote
                j++;
                swap(a, j, k);
            }
        }
        swap(a, j + 1, h); // coloca el pivote en su posición correcta
        return j + 1;
    }

    // Implementación de la función QuickSort 
    static void qckSort(int[] a, int l, int h) {
        if (l < h) {
            int pi = partition(a, l, h);
            qckSort(a, l, pi - 1);
            qckSort(a, pi + 1, h);
        }
    }

    public static void main(String[] args) {
        int[] a = {10, 7, 8, 9, 1, 5}; // arreglo desordenado
        int size = a.length;

        System.out.println("El arreglo antes de ordenarlo:");
        for (int v : a) System.out.print(v + " ");
        System.out.println();

        qckSort(a, 0, size - 1);

        System.out.println("El arreglo después de ordenarlo:");
        for (int v : a) System.out.print(v + " ");
    }
}