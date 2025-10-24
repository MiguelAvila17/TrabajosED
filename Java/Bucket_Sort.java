import java.util.*;

public class Bucket_Sort {

    static void insertionSort(List<Double> bukt) {
        for (int j = 1; j < bukt.size(); j++) {
            double val = bukt.get(j);
            int k = j - 1;
            while (k >= 0 && bukt.get(k) > val) {
                bukt.set(k + 1, bukt.get(k));
                k--;
            }
            bukt.set(k + 1, val);
        }
    }

    static void bucketSort(double[] arr) {
        int s = arr.length;
        List<Double>[] buckets = new List[s];
        for (int i = 0; i < s; i++)
            buckets[i] = new ArrayList<>();

        for (double num : arr) {
            int bi = (int)(s * num);
            if (bi >= s) bi = s - 1;
            buckets[bi].add(num);
        }

        for (List<Double> b : buckets)
            insertionSort(b);

        int idx = 0;
        for (List<Double> b : buckets)
            for (double num : b)
                arr[idx++] = num;
    }

    public static void main(String[] args) {
        double[] inputArr = {0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67};

        System.out.println("Arreglo antes de ordenar:");
        for (double x : inputArr) System.out.print(x + " ");
        System.out.println();

        bucketSort(inputArr);

        System.out.println("Arreglo después de ordenar:");
        for (double x : inputArr) System.out.print(x + " ");
        System.out.println();
    }
}