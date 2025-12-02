// Clase para representar un nodo
class NodeBST {
    int data;
    NodeBST leftNode;
    NodeBST rightNode;

    public NodeBST(int data) {
        this.data = data;
        this.leftNode = null;
        this.rightNode = null;
    }
}

class BinarySearchTree {
    NodeBST rootNode;

    public BinarySearchTree() {
        this.rootNode = null;
    }

    // Método de ayuda para encontrar el valor mínimo (sucesor inorden)
    private NodeBST findMin(NodeBST node) {
        while (node.leftNode != null) {
            node = node.leftNode;
        }
        return node;
    }

    // --- INSERCIÓN ---
    public void insert(int data) {
        rootNode = insertRec(rootNode, data);
    }

    private NodeBST insertRec(NodeBST currentNode, int data) {
        if (currentNode == null) {
            return new NodeBST(data);
        }

        if (data < currentNode.data) {
            currentNode.leftNode = insertRec(currentNode.leftNode, data);
        } else if (data > currentNode.data) {
            currentNode.rightNode = insertRec(currentNode.rightNode, data);
        }
        
        return currentNode;
    }

    // --- ELIMINACIÓN ---
    public void delete(int data) {
        rootNode = deleteRec(rootNode, data);
    }

    private NodeBST deleteRec(NodeBST currentNode, int data) {
        if (currentNode == null) {
            return null;
        }

        if (data < currentNode.data) {
            currentNode.leftNode = deleteRec(currentNode.leftNode, data);
        } else if (data > currentNode.data) {
            currentNode.rightNode = deleteRec(currentNode.rightNode, data);
        } else { // Nodo encontrado
            // Caso 1 y 2: 0 o 1 hijo
            if (currentNode.leftNode == null) {
                return currentNode.rightNode;
            }
            if (currentNode.rightNode == null) {
                return currentNode.leftNode;
            }

            // Caso 3: Dos hijos
            NodeBST successor = findMin(currentNode.rightNode);
            currentNode.data = successor.data;
            currentNode.rightNode = deleteRec(currentNode.rightNode, successor.data);
        }

        return currentNode;
    }
    
    // --- RECORRIDO INORDEN ---
    public void inorder() {
        inorderRec(rootNode);
        System.out.println();
    }

    private void inorderRec(NodeBST node) {
        if (node != null) {
            inorderRec(node.leftNode);
            System.out.print(node.data + " ");
            inorderRec(node.rightNode);
        }
    }
}