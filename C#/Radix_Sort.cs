using System;

class RadixSort
{
    public static void RadixSort(int[] arr)
    {
        int max = 0;
        foreach (int num in arr) if (num > max) max = num;
        int n = arr.Length;

        for (int exp = 1; max / exp > 0; exp *= 10)
        {
            int[] output = new int[n];
            int[] count = new int[10];

            for (int i = 0; i < n; i++)
                count[(arr[i] / exp) % 10]++;

            for (int i = 1; i < 10; i++)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; i--)
            {
                int index = (arr[i] / exp) % 10;
                output[count[index] - 1] = arr[i];
                count[index]--;
            }

            for (int i = 0; i < n; i++)
                arr[i] = output[i];
        }
    }

    static void Main()
    {
        int[] arr = {170, 45, 75, 90, 802, 24, 2, 66};
        RadixSort(arr);
        Console.WriteLine("Arreglo ordenado: " + string.Join(", ", arr));
    }
}