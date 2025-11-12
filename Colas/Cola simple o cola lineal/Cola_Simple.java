import java.util.Scanner;

public class Cola_Simple {
    static final int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;
    static Scanner sc = new Scanner(System.in);

    static void insertar() {
        if (rear == MAXSIZE - 1) {
            System.out.println("OVERFLOW");
            return;
        }
        System.out.print("Ingrese el elemento: ");
        int elemento = sc.nextInt();
        if (front == -1 && rear == -1) {
            front = rear = 0;
        } else {
            rear++;
        }
        queue[rear] = elemento;
        System.out.println("Elemento insertado correctamente.");
    }

    static void eliminar() {
        if (front == -1 || front > rear) {
            System.out.println("UNDERFLOW");
            return;
        }
        System.out.println("Elemento eliminado: " + queue[front]);
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
    }

    static void mostrar() {
        if (rear == -1 || front == -1 || front > rear) {
            System.out.println("La cola está vacía.");
        } else {
            System.out.println("Elementos en la cola:");
            for (int i = front; i <= rear; i++) {
                System.out.println(queue[i]);
            }
        }
    }

    public static void main(String[] args) {
        int op;
        do {
            System.out.println("\n*************** COLA SIMPLE ***************");
            System.out.println("1.Insertar 2.Eliminar 3.Mostrar 4.Salir");
            System.out.print("Opción: ");
            op = sc.nextInt();

            switch (op) {
                case 1 -> insertar();
                case 2 -> eliminar();
                case 3 -> mostrar();
                case 4 -> System.out.println("Saliendo...");
                default -> System.out.println("Opción inválida.");
            }
        } while (op != 4);
    }
}