import java.util.Scanner;

// Clase para representar un nodo
class Node {
    int data;
    Node left;
    Node right;

    public Node(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

class BinaryTreeCreator {
    private static Scanner scanner = new Scanner(System.in);

    // Función para crear un árbol binario de forma recursiva
    public static Node createTree() {
        int choice;
        int data;

        System.out.println("Presiona 0 para salir");
        System.out.println("Presiona 1 para un nuevo nodo");
        System.out.print("Ingresa la opción: ");

        // Manejo básico de entrada de enteros
        if (!scanner.hasNextInt()) {
            System.out.println("Entrada no válida. Terminando subárbol actual.");
            scanner.next(); // Limpia la entrada no válida
            return null;
        }
        choice = scanner.nextInt();

        if (choice == 0) {
            return null;
        } else if (choice == 1) {
            System.out.print("Ingresa los datos: ");
            data = scanner.nextInt();

            Node temp = new Node(data);

            System.out.println("Ingresa el nodo hijo izquierdo de " + data);
            temp.left = createTree(); // Llamada recursiva

            System.out.println("Ingresa el nodo hijo derecho de " + data);
            temp.right = createTree(); // Llamada recursiva

            return temp;
        } else {
            System.out.println("Opción no válida. Terminando subárbol actual.");
            return null;
        }
    }
}

/*
// Ejemplo de uso en la clase principal
public class Main {
    public static void main(String[] args) {
        Node root = BinaryTreeCreator.createTree();
        // Nota: El scanner de System.in permanece abierto en el ejemplo.
    }
}
*/