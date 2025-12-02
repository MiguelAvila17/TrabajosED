#include <iostream>
#include <cstdlib> // Para new

// Definición de la estructura del nodo del árbol binario
struct Node {
    int data;
    Node *left;
    Node *right;
};

// Función para crear un árbol binario de forma recursiva
Node* createTree() {
    int choice;
    int data;

    std::cout << "Presiona 0 para salir" << std::endl;
    std::cout << "Presiona 1 para un nuevo nodo" << std::endl;
    std::cout << "Ingresa la opción: ";
    
    // Captura de entrada con manejo de errores básico
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return nullptr;
    }

    if (choice == 0) {
        return nullptr;
    } else {
        std::cout << "Ingresa los datos: ";
        std::cin >> data;

        // Crear un nuevo nodo
        Node* temp = new Node;
        temp->data = data;
        temp->left = nullptr;
        temp->right = nullptr;

        std::cout << "Ingresa el nodo hijo izquierdo de " << data << std::endl;
        temp->left = createTree(); // Llamada recursiva

        std::cout << "Ingresa el nodo hijo derecho de " << data << std::endl;
        temp->right = createTree(); // Llamada recursiva

        return temp;
    }
}

/*
int main() {
    Node* root = createTree();
    // Uso del árbol...
    return 0;
}
*/