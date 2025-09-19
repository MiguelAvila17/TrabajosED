import java.util.Random;

public class ordenacion_insercion {
    public static void insertionSort(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
    }

    public static void main(String[] args) {
        Random rand = new Random();
        int[] arr = new int[10];
        for (int i = 0; i < arr.length; i++) arr[i] = rand.nextInt(100) + 1;

        System.out.print("Antes de ordenar: ");
        for (int x : arr) System.out.print(x + " ");
        System.out.println();

        insertionSort(arr);

        System.out.print("Después de ordenar: ");
        for (int x : arr) System.out.print(x + " ");
        System.out.println();
    }
}