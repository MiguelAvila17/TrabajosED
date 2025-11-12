import java.util.Scanner;

public class ColaCircular {
    static final int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;
    static Scanner sc = new Scanner(System.in);

    static boolean estaVacia() { return front == -1; }
    static boolean estaLlena() { return (rear + 1) % MAXSIZE == front; }

    static void insertar() {
        System.out.print("Ingrese el elemento: ");
        int elemento = sc.nextInt();
        if (estaLlena()) { System.out.println("OVERFLOW"); return; }
        if (estaVacia()) front = rear = 0;
        else rear = (rear + 1) % MAXSIZE;
        queue[rear] = elemento;
        System.out.println("Elemento insertado.");
    }

    static void eliminar() {
        if (estaVacia()) { System.out.println("UNDERFLOW"); return; }
        System.out.println("Elemento eliminado: " + queue[front]);
        if (front == rear) front = rear = -1;
        else front = (front + 1) % MAXSIZE;
    }

    static void mostrar() {
        if (estaVacia()) { System.out.println("Cola vacía"); return; }
        System.out.print("Cola: ");
        int i = front;
        while (true) {
            System.out.print(queue[i] + " ");
            if (i == rear) break;
            i = (i + 1) % MAXSIZE;
        }
        System.out.println();
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