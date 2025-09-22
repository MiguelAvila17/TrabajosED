import java.util.Random;

public class ordenamiento_seleccion {
    public static void selectionSort(int[] a) {
        for (int i = 0; i < a.length; i++) {
            int small = i;
            for (int j = i + 1; j < a.length; j++) {
                if (a[small] > a[j]) {
                    small = j;
                }
            }
            int temp = a[i];
            a[i] = a[small];
            a[small] = temp;
        }
    }

    public static void printArr(int[] a) {
        for (int num : a) {
            System.out.print(num + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Random rand = new Random();
        int[] a = new int[5];
        for (int i = 0; i < a.length; i++) {
            a[i] = rand.nextInt(100) + 1;
        }

        System.out.println("Arreglo antes de ser ordenado:");
        printArr(a);

        selectionSort(a);

        System.out.println("\nArreglo después de ser ordenado:");
        printArr(a);
    }
}