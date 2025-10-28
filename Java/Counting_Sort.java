import java.util.Arrays;

public class Counting_Sort {
    public static void countingSort(int[] arr) {
        if (arr.length == 0) return;

        int maxVal = Arrays.stream(arr).max().getAsInt();
        int[] count = new int[maxVal + 1];

        for (int num : arr)
            count[num]++;

        int index = 0;
        for (int i = 0; i <= maxVal; i++)
            while (count[i]-- > 0)
                arr[index++] = i;
    }

    public static void main(String[] args) {
        int[] arr = {4, 2, 2, 8, 3, 3, 1};
        countingSort(arr);
        System.out.println(Arrays.toString(arr));
    }
}