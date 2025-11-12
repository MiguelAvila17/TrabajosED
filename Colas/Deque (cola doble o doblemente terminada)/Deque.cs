using System;
using System.Collections.Generic;

class Deque {
    const int MAXSIZE = 5;
    static LinkedList<int> dq = new LinkedList<int>();

    static void InsertarFrente() {
        if (dq.Count == MAXSIZE) { Console.WriteLine("OVERFLOW"); return; }
        Console.Write("Elemento: ");
        int e = int.Parse(Console.ReadLine());
        dq.AddFirst(e);
        Console.WriteLine("Insertado al frente.");
    }

    static void InsertarFinal() {
        if (dq.Count == MAXSIZE) { Console.WriteLine("OVERFLOW"); return; }
        Console.Write("Elemento: ");
        int e = int.Parse(Console.ReadLine());
        dq.AddLast(e);
        Console.WriteLine("Insertado al final.");
    }

    static void EliminarFrente() {
        if (dq.Count == 0) { Console.WriteLine("UNDERFLOW"); return; }
        Console.WriteLine("Eliminado del frente: " + dq.First.Value);
        dq.RemoveFirst();
    }

    static void EliminarFinal() {
        if (dq.Count == 0) { Console.WriteLine("UNDERFLOW"); return; }
        Console.WriteLine("Eliminado del final: " + dq.Last.Value);
        dq.RemoveLast();
    }

    static void Mostrar() {
        Console.WriteLine("Deque: " + string.Join(", ", dq));
    }

    static void Main() {
        int op;
        do {
            Console.WriteLine("\n1.Insertar frente 2.Insertar final 3.Eliminar frente 4.Eliminar final 5.Mostrar 6.Salir");
            op = int.Parse(Console.ReadLine());
            switch (op) {
                case 1: InsertarFrente(); break;
                case 2: InsertarFinal(); break;
                case 3: EliminarFrente(); break;
                case 4: EliminarFinal(); break;
                case 5: Mostrar(); break;
            }
        } while (op != 6);
    }
}