using System;

class Cola_Simple {
    const int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;

    static void Insertar() {
        if (rear == MAXSIZE - 1) {
            Console.WriteLine("OVERFLOW");
            return;
        }
        Console.Write("Ingrese el elemento: ");
        int elemento = int.Parse(Console.ReadLine());
        if (front == -1 && rear == -1) {
            front = rear = 0;
        } else {
            rear++;
        }
        queue[rear] = elemento;
        Console.WriteLine("Elemento insertado correctamente.");
    }

    static void Eliminar() {
        if (front == -1 || front > rear) {
            Console.WriteLine("UNDERFLOW");
            return;
        }
        Console.WriteLine("Elemento eliminado: " + queue[front]);
        if (front == rear) front = rear = -1;
        else front++;
    }

    static void Mostrar() {
        if (rear == -1 || front == -1 || front > rear) {
            Console.WriteLine("La cola está vacía.");
        } else {
            Console.WriteLine("Elementos en la cola:");
            for (int i = front; i <= rear; i++)
                Console.WriteLine(queue[i]);
        }
    }

    static void Main() {
        int opcion;
        do {
            Console.WriteLine("\n*************** COLA SIMPLE ***************");
            Console.WriteLine("1.Insertar\n2.Eliminar\n3.Mostrar\n4.Salir");
            Console.Write("Opción: ");
            opcion = int.Parse(Console.ReadLine());

            switch (opcion) {
                case 1: Insertar(); break;
                case 2: Eliminar(); break;
                case 3: Mostrar(); break;
                case 4: Console.WriteLine("Saliendo..."); break;
                default: Console.WriteLine("Opción inválida."); break;
            }
        } while (opcion != 4);
    }
}