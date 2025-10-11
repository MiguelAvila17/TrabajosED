using System;
using System.Collections.Generic;

class Program
{
    static void InsertionSort(List<double> bukt)
    {
        for (int j = 1; j < bukt.Count; j++)
        {
            double val = bukt[j];
            int k = j - 1;
            while (k >= 0 && bukt[k] > val)
            {
                bukt[k + 1] = bukt[k];
                k--;
            }
            bukt[k + 1] = val;
        }
    }

    static void BucketSort(double[] arr)
    {
        int s = arr.Length;
        List<double>[] buckets = new List<double>[s];
        for (int i = 0; i < s; i++)
            buckets[i] = new List<double>();

        foreach (double num in arr)
        {
            int bi = (int)(s * num);
            if (bi >= s) bi = s - 1;
            buckets[bi].Add(num);
        }

        foreach (var b in buckets)
            InsertionSort(b);

        int idx = 0;
        foreach (var b in buckets)
            foreach (var num in b)
                arr[idx++] = num;
    }

    static void Main()
    {
        double[] inputArr = { 0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67 };
        Console.WriteLine("Arreglo antes de ordenar:");
        Console.WriteLine(string.Join(" ", inputArr));

        BucketSort(inputArr);

        Console.WriteLine("Arreglo después de ordenar:");
        Console.WriteLine(string.Join(" ", inputArr));
    }
}