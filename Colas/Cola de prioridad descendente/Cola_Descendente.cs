using System;
using System.Collections.Generic;

class ColaPrioridadDescendente {
    const int MAXSIZE = 5;
    static List<int> queue = new List<int>();

    static void Insertar() {
        if (queue.Count == MAXSIZE) { Console.WriteLine("OVERFLOW"); return; }
        Console.Write("Ingrese el elemento: ");
        int e = int.Parse(Console.ReadLine());
        queue.Add(e);
        queue.Sort((a, b) => b.CompareTo(a));
        Console.WriteLine("Elemento insertado.");
    }

    static void Eliminar() {
        if (queue.Count == 0) { Console.WriteLine("UNDERFLOW"); return; }
        Console.WriteLine("Elemento eliminado: " + queue[0]);
        queue.RemoveAt(0);
    }

    static void Mostrar() {
        if (queue.Count == 0) Console.WriteLine("Vacía");
        else Console.WriteLine("Cola: " + string.Join(", ", queue));
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