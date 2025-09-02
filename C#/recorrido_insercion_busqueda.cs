using System;
class Program {
    static void Main() {
        int[] arr = {10, 20, 30, 40, 50};

        // 1. Recorrido
        Console.WriteLine("Recorrido del arreglo:");
        foreach (int i in arr) {
            Console.WriteLine(i);
        }

        // 2. Insertar en índice (usando lista para facilidad)
        var lista = new System.Collections.Generic.List<int>(arr);
        lista.Insert(2, 99);
        Console.WriteLine("Después de insertar: " + string.Join(", ", lista));

        // 3. Búsqueda lineal
        int x = 30;
        bool encontrado = false;
        for (int i = 0; i < lista.Count; i++) {
            if (lista[i] == x) {
                Console.WriteLine($"Elemento {x} encontrado en índice {i}");
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
            Console.WriteLine($"Elemento {x} no encontrado");
    }
}
