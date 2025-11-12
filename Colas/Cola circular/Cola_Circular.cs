using System;

class ColaCircular {
    const int MAXSIZE = 5;
    static int[] queue = new int[MAXSIZE];
    static int front = -1, rear = -1;

    static bool EstaVacia() => front == -1;
    static bool EstaLlena() => (rear + 1) % MAXSIZE == front;

    static void Insertar() {
        Console.Write("Ingrese el elemento: ");
        int elemento = int.Parse(Console.ReadLine());
        if (EstaLlena()) { Console.WriteLine("OVERFLOW"); return; }

        if (EstaVacia()) front = rear = 0;
        else rear = (rear + 1) % MAXSIZE;
        queue[rear] = elemento;
        Console.WriteLine("Elemento insertado.");
    }

    static void Eliminar() {
        if (EstaVacia()) { Console.WriteLine("UNDERFLOW"); return; }
        Console.WriteLine($"Elemento eliminado: {queue[front]}");
        if (front == rear) front = rear = -1;
        else front = (front + 1) % MAXSIZE;
    }

    static void Mostrar() {
        if (EstaVacia()) { Console.WriteLine("Vacía"); return; }
        int i = front;
        Console.Write("Cola: ");
        while (true) {
            Console.Write(queue[i] + " ");
            if (i == rear) break;
            i = (i + 1) % MAXSIZE;
        }
        Console.WriteLine();
    }

    static void Main() {
        int op;
        do {
            Console.WriteLine("\n1.Insertar 2.Eliminar 3.Mostrar 4.Salir");
            op = int.Parse(Console.ReadLine());
            switch (op) {
                case 1: Insertar(); break;
                case 2: Eliminar(); break;
                case 3: Mostrar(); break;
            }
        } while (op != 4);
    }
}