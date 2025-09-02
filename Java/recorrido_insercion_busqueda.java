import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50};

        // 1. Recorrido
        System.out.println("Recorrido del arreglo:");
        for (int i : arr) {
            System.out.println(i);
        }

        // 2. Insertar en índice (usando ArrayList)
        ArrayList<Integer> lista = new ArrayList<>();
        for (int i : arr) lista.add(i);
        lista.add(2, 99);
        System.out.println("Después de insertar: " + lista);

        // 3. Búsqueda lineal
        int x = 30;
        boolean encontrado = false;
        for (int i = 0; i < lista.size(); i++) {
            if (lista.get(i) == x) {
                System.out.println("Elemento " + x + " encontrado en índice " + i);
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
            System.out.println("Elemento " + x + " no encontrado");
    }
}
