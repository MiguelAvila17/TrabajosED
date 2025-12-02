// Clase para representar un nodo
class Node {
    constructor(data) {
        this.data = data;
        this.leftNode = null;
        this.rightNode = null;
    }
}

class BinarySearchTree {
    constructor() {
        this.rootNode = null;
    }

    // Método de ayuda para encontrar el valor mínimo (sucesor inorden)
    _findMin(node) {
        while (node.leftNode) {
            node = node.leftNode;
        }
        return node;
    }

    // --- INSERCIÓN ---
    insert(data) {
        this.rootNode = this._insertRec(this.rootNode, data);
    }

    _insertRec(currentNode, data) {
        if (currentNode === null) {
            return new Node(data);
        }

        if (data < currentNode.data) {
            currentNode.leftNode = this._insertRec(currentNode.leftNode, data);
        } else if (data > currentNode.data) {
            currentNode.rightNode = this._insertRec(currentNode.rightNode, data);
        }
        
        return currentNode;
    }

    // --- ELIMINACIÓN ---
    delete(data) {
        this.rootNode = this._deleteRec(this.rootNode, data);
    }

    _deleteRec(currentNode, data) {
        if (currentNode === null) {
            return null;
        }

        if (data < currentNode.data) {
            currentNode.leftNode = this._deleteRec(currentNode.leftNode, data);
        } else if (data > currentNode.data) {
            currentNode.rightNode = this._deleteRec(currentNode.rightNode, data);
        } else { // Nodo encontrado
            // Caso 1 y 2: 0 o 1 hijo
            if (currentNode.leftNode === null) {
                return currentNode.rightNode;
            }
            if (currentNode.rightNode === null) {
                return currentNode.leftNode;
            }

            // Caso 3: Dos hijos
            let successor = this._findMin(currentNode.rightNode);
            currentNode.data = successor.data;
            currentNode.rightNode = this._deleteRec(currentNode.rightNode, successor.data);
        }

        return currentNode;
    }
    
    // --- RECORRIDO INORDEN ---
    inorder() {
        this._inorderRec(this.rootNode);
        console.log();
    }

    _inorderRec(node) {
        if (node) {
            this._inorderRec(node.leftNode);
            // Uso de process.stdout.write para simular print(..., end=" ") en Node.js
            process.stdout.write(node.data + " "); 
            this._inorderRec(node.rightNode);
        }
    }
}

/*
// Ejemplo de uso:
const bst = new BinarySearchTree();
// ... (Insertar y usar métodos)
*/