import java.util.*;

public class Cola_Descendente {
    static final int MAXSIZE = 5;
    static List<Integer> queue = new ArrayList<>();
    static Scanner sc = new Scanner(System.in);

    static void insertar() {
        if (queue.size() == MAXSIZE) { System.out.println("OVERFLOW"); return; }
        System.out.print("Ingrese el elemento: ");
        int e = sc.nextInt();
        queue.add(e);
        queue.sort(Collections.reverseOrder());
        System.out.println("Elemento insertado.");
    }

    static void eliminar() {
        if (queue.isEmpty()) { System.out.println("UNDERFLOW"); return; }
        System.out.println("Elemento eliminado: " + queue.remove(0));
    }

    static void mostrar() {
        if (queue.isEmpty()) System.out.println("Vacía");
        else System.out.println("Cola descendente: " + queue);
    }

    public static void main(String[] args) {
        int op;
        do {
            System.out.println("\n1.Insertar 2.Eliminar 3.Mostrar 4.Salir");
            op = sc.nextInt();
            switch (op) {
                case 1 -> insertar();
                case 2 -> eliminar();
                case 3 -> mostrar();
            }
        } while (op != 4);
    }
}