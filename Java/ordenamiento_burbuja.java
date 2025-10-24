import java.util.Random;

public class ordenamiento_burbuja {
    static void burbuja(int arr[]) {
        int n = arr.length;
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

    public static void main(String[] args) {
        Random rnd = new Random();
        int arr[] = new int[10];

        for (int i = 0; i < arr.length; i++) {
            arr[i] = rnd.nextInt(100) + 1; // números entre 1 y 100
        }

        System.out.print("Original: ");
        for (int num : arr) System.out.print(num + " ");
        System.out.println();

        burbuja(arr);

        System.out.print("Ordenado: ");
        for (int num : arr) System.out.print(num + " ");
    }
}