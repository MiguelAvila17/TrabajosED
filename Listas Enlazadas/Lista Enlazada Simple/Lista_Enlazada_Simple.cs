using System;

class Nodo
{
    public int Dato;
    public Nodo Siguiente;

    public Nodo(int dato)
    {
        Dato = dato;
        Siguiente = null;
    }
}

class ListaEnlazada
{
    private Nodo cabeza;

    public void Agregar(int dato)
    {
        Nodo nuevo = new Nodo(dato);
        if (cabeza == null)
            cabeza = nuevo;
        else
        {
            Nodo actual = cabeza;
            while (actual.Siguiente != null)
                actual = actual.Siguiente;
            actual.Siguiente = nuevo;
        }
    }

    public void Mostrar()
    {
        Nodo actual = cabeza;
        Console.WriteLine("\nLista enlazada:");
        while (actual != null)
        {
            Console.Write(actual.Dato + " -> ");
            actual = actual.Siguiente;
        }
        Console.WriteLine("NULL\n");
    }
}

class Program
{
    static void Main()
    {
        ListaEnlazada lista = new ListaEnlazada();
        int opcion, dato;

        do
        {
            Console.WriteLine("=== LISTA ENLAZADA (C#) ===");
            Console.WriteLine("1. Agregar nodo");
            Console.WriteLine("2. Mostrar lista");
            Console.WriteLine("3. Salir");
            Console.Write("Opción: ");
            opcion = int.Parse(Console.ReadLine() ?? "0");

            switch (opcion)
            {
                case 1:
                    Console.Write("Dato: ");
                    dato = int.Parse(Console.ReadLine() ?? "0");
                    lista.Agregar(dato);
                    break;
                case 2:
                    lista.Mostrar();
                    break;
            }
        } while (opcion != 3);
    }
}