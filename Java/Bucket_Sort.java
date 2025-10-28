import java.util.List;
import java.util.ArrayList;

public class Bucket_Sort {

    // Método de ordenamiento por inserción para cada cubeta
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

    // Método principal del algoritmo Bucket Sort
    static void bucketSort(double[] arr) {
        int s = arr.length;
        @SuppressWarnings("unchecked")
        List<Double>[] buckets = (List<Double>[]) new List[s]; // CORREGIDO
        for (int i = 0; i < s; i++)
            buckets[i] = new ArrayList<>();

        // Distribuir los elementos en cubetas
        for (double num : arr) {
            int bi = (int)(s * num);
            if (bi >= s) bi = s - 1;
            buckets[bi].add(num);
        }

        // Ordenar cada cubeta
        for (List<Double> b : buckets)
            insertionSort(b);

        // Combinar las cubetas
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