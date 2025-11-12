import java.util.*;

public class DequeEjemplo {
    static final int MAXSIZE = 5;
    static Deque<Integer> dq = new ArrayDeque<>();
    static Scanner sc = new Scanner(System.in);

    static void insertarFrente() {
        if (dq.size() == MAXSIZE) { System.out.println("OVERFLOW"); return; }
        System.out.print("Elemento: ");
        dq.addFirst(sc.nextInt());
        System.out.println("Insertado al frente.");
    }

    static void insertarFinal() {
        if (dq.size() == MAXSIZE) { System.out.println("OVERFLOW"); return; }
        System.out.print("Elemento: ");
        dq.addLast(sc.nextInt());
        System.out.println("Insertado al final.");
    }

    static void eliminarFrente() {
        if (dq.isEmpty()) { System.out.println("UNDERFLOW"); return; }
        System.out.println("Eliminado del frente: " + dq.removeFirst());
    }

    static void eliminarFinal() {
        if (dq.isEmpty()) { System.out.println("UNDERFLOW"); return; }
        System.out.println("Eliminado del final: " + dq.removeLast());
    }

    static void mostrar() {
        System.out.println("Deque: " + dq);
    }

    public static void main(String[] args) {
        int op;
        do {
            System.out.println("\n1.Insertar frente 2.Insertar final 3.Eliminar frente 4.Eliminar final 5.Mostrar 6.Salir");
            op = sc.nextInt();
            switch (op) {
                case 1 -> insertarFrente();
                case 2 -> insertarFinal();
                case 3 -> eliminarFrente();
                case 4 -> eliminarFinal();
                case 5 -> mostrar();
            }
        } while (op != 6);
    }
}