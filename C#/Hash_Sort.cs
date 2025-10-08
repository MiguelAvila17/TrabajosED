using System;
using System.Collections.Generic;

class Program
{
    static void HashSort(List<int> arr)
    {
        Dictionary<int, int> hashTable = new Dictionary<int, int>();
        int maxVal = 0;

        foreach (int num in arr)
        {
            if (hashTable.ContainsKey(num))
                hashTable[num]++;
            else
                hashTable[num] = 1;

            if (num > maxVal) maxVal = num;
        }

        arr.Clear();
        for (int i = 0; i <= maxVal; i++)
        {
            if (hashTable.ContainsKey(i))
            {
                for (int j = 0; j < hashTable[i]; j++)
                    arr.Add(i);
            }
        }
    }

    static void Main()
    {
        List<int> arr = new List<int> { 4, 2, 2, 8, 3, 3, 1 };

        Console.WriteLine("Arreglo original: " + string.Join(" ", arr));

        HashSort(arr);

        Console.WriteLine("Arreglo ordenado: " + string.Join(" ", arr));
    }
}