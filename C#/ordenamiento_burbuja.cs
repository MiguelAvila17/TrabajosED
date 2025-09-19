using System;

class Programa {
    static void Burbuja(int[] arr) {
        int n = arr.Length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    static void Main() {
        Random rnd = new Random();
        int[] arr = new int[10];
        
        for (int i = 0; i < arr.Length; i++) {
            arr[i] = rnd.Next(1, 101); // números entre 1 y 100
        }

        Console.WriteLine("Original: " + string.Join(", ", arr));
        Burbuja(arr);
        Console.WriteLine("Ordenado: " + string.Join(", ", arr));
    }
}