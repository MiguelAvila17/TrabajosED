#include <iostream>
#include <algorithm> // Para std::max o simplemente lógica

// Definición de la estructura del nodo
struct Node {
    int data;
    Node *leftNode;
    Node *rightNode;

    Node(int data) : data(data), leftNode(nullptr), rightNode(nullptr) {}
};

class BinarySearchTree {
public:
    Node *rootNode;

    BinarySearchTree() : rootNode(nullptr) {}

    // --- MÉTODOS PÚBLICOS ---
    void insert(int data) {
        rootNode = insertRec(rootNode, data);
    }

    void deleteNode(int data) {
        rootNode = deleteRec(rootNode, data);
    }

    void inorder() {
        inorderRec(rootNode);
        std::cout << std::endl;
    }

private:
    // --- MÉTODOS PRIVADOS RECURSIVOS ---

    Node* findMin(Node* node) {
        while (node && node->leftNode) {
            node = node->leftNode;
        }
        return node;
    }

    Node* insertRec(Node* currentNode, int data) {
        if (currentNode == nullptr) {
            return new Node(data);
        }

        if (data < currentNode->data) {
            currentNode->leftNode = insertRec(currentNode->leftNode, data);
        } else if (data > currentNode->data) {
            currentNode->rightNode = insertRec(currentNode->rightNode, data);
        }
        
        return currentNode;
    }

    Node* deleteRec(Node* currentNode, int data) {
        if (currentNode == nullptr) {
            return nullptr;
        }

        if (data < currentNode->data) {
            currentNode->leftNode = deleteRec(currentNode->leftNode, data);
        } else if (data > currentNode->data) {
            currentNode->rightNode = deleteRec(currentNode->rightNode, data);
        } else { // Nodo encontrado
            // Caso 1 y 2: 0 o 1 hijo
            if (currentNode->leftNode == nullptr) {
                Node* temp = currentNode->rightNode;
                delete currentNode;
                return temp;
            }
            if (currentNode->rightNode == nullptr) {
                Node* temp = currentNode->leftNode;
                delete currentNode;
                return temp;
            }

            // Caso 3: Dos hijos (reemplazar con el sucesor inorden)
            Node* successor = findMin(currentNode->rightNode);
            currentNode->data = successor->data;
            currentNode->rightNode = deleteRec(currentNode->rightNode, successor->data);
        }
        return currentNode;
    }

    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->leftNode);
            std::cout << node->data << " ";
            inorderRec(node->rightNode);
        }
    }
};

/*
// Ejemplo de uso:
int main() {
    BinarySearchTree bst;
    bst.insert(45); 
    bst.insert(30);
    // ...
    bst.inorder();
    bst.deleteNode(25);
    bst.inorder();
    return 0;
}
*/