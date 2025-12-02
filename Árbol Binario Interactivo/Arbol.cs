using System;

// Clase para representar un nodo
public class Node
{
    public int data;
    public Node left;
    public Node right;

    public Node(int data)
    {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class BinaryTreeCreator
{
    // Función para crear un árbol binario de forma recursiva
    public static Node CreateTree()
    {
        int choice;
        int data;

        while (true)
        {
            Console.WriteLine("Presiona 0 para salir");
            Console.WriteLine("Presiona 1 para un nuevo nodo");
            Console.Write("Ingresa la opción: ");

            // Captura de entrada
            if (!int.TryParse(Console.ReadLine(), out choice))
            {
                Console.WriteLine("Entrada no válida. Intenta de nuevo.");
                continue;
            }

            if (choice == 0)
            {
                return null;
            }
            else if (choice == 1)
            {
                Console.Write("Ingresa los datos: ");
                if (!int.TryParse(Console.ReadLine(), out data))
                {
                    Console.WriteLine("Entrada de datos no válida. Intenta de nuevo.");
                    continue;
                }

                Node temp = new Node(data);

                Console.WriteLine($"Ingresa el nodo hijo izquierdo de {data}");
                temp.left = CreateTree(); // Llamada recursiva

                Console.WriteLine($"Ingresa el nodo hijo derecho de {data}");
                temp.right = CreateTree(); // Llamada recursiva

                return temp;
            }
            else
            {
                Console.WriteLine("Opción no válida. Intenta de nuevo.");
            }
        }
    }
}

/*
// Ejemplo de uso
public class Program
{
    public static void Main(string[] args)
    {
        Node root = BinaryTreeCreator.CreateTree();
        // Uso del árbol...
    }
}
*/