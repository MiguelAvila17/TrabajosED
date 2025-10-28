using System;

class Program {
    static void CountingSort(int[] arr) {
        if (arr.Length == 0) return;

        int maxVal = arr[0];
        foreach (int num in arr)
            if (num > maxVal) maxVal = num;

        int[] count = new int[maxVal + 1];

        foreach (int num in arr)
            count[num]++;

        int index = 0;
        for (int i = 0; i <= maxVal; i++)
            while (count[i]-- > 0)
                arr[index++] = i;
    }

    static void Main() {
        int[] arr = {4, 2, 2, 8, 3, 3, 1};
        CountingSort(arr);
        Console.WriteLine(string.Join(" ", arr));
    }
}