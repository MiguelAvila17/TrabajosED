using System;

class SelectionSort {
    static void Selection(int[] a) {
        for (int i = 0; i < a.Length; i++) {
            int small = i;
            for (int j = i + 1; j < a.Length; j++) {
                if (a[small] > a[j]) {
                    small = j;
                }
            }
            int temp = a[i];
            a[i] = a[small];
            a[small] = temp;
        }
    }

    static void PrintArr(int[] a) {
        foreach (int num in a) {
            Console.Write(num + " ");
        }
        Console.WriteLine();
    }

    static void Main() {
        Random rand = new Random();
        int[] a = new int[5];
        for (int i = 0; i < a.Length; i++) {
            a[i] = rand.Next(1, 101);
        }

        Console.WriteLine("Arreglo antes de ser ordenado:");
        PrintArr(a);

        Selection(a);

        Console.WriteLine("\nArreglo después de ser ordenado:");
        PrintArr(a);
    }
}