class Node:
    def __init__(self, data):
        self.data = data
        self.leftNode = None
        self.rightNode = None

class BinarySearchTree:
    def __init__(self):
        self.rootNode = None

    # Método para encontrar el valor mínimo (sucesor inorden)
    def _findMin(self, node):
        while node.leftNode:
            node = node.leftNode
        return node

    # --- INSERCIÓN ---
    def insert(self, data):
        self.rootNode = self._insertRec(self.rootNode, data)

    def _insertRec(self, currentNode, data):
        if currentNode is None:
            return Node(data)

        if data < currentNode.data:
            currentNode.leftNode = self._insertRec(currentNode.leftNode, data)
        elif data > currentNode.data:
            currentNode.rightNode = self._insertRec(currentNode.rightNode, data)
        
        return currentNode

    # --- ELIMINACIÓN ---
    def delete(self, data):
        self.rootNode = self._deleteRec(self.rootNode, data)

    def _deleteRec(self, currentNode, data):
        if currentNode is None:
            return None

        if data < currentNode.data:
            currentNode.leftNode = self._deleteRec(currentNode.leftNode, data)
        elif data > currentNode.data:
            currentNode.rightNode = self._deleteRec(currentNode.rightNode, data)
        else: # Se encontró el nodo a eliminar
            # Caso 1 y 2: 0 o 1 hijo
            if currentNode.leftNode is None:
                return currentNode.rightNode
            if currentNode.rightNode is None:
                return currentNode.leftNode
            
            # Caso 3: Dos hijos
            successor = self._findMin(currentNode.rightNode)
            currentNode.data = successor.data
            currentNode.rightNode = self._deleteRec(currentNode.rightNode, successor.data)

        return currentNode

    # --- RECORRIDO INORDEN ---
    def inorder(self):
        self._inorderRec(self.rootNode)
        print()

    def _inorderRec(self, node):
        if node:
            self._inorderRec(node.leftNode)
            print(node.data, end=" ")
            self._inorderRec(node.rightNode)

# Ejemplo de uso (basado en el PDF):
if __name__ == "__main__":
    bst = BinarySearchTree()
    bst.insert(45) 
    bst.insert(30)
    bst.insert(50)
    bst.insert(25)
    bst.insert(35)
    bst.insert(60)
    bst.insert(4)
    print("El recorrido en orden del árbol de búsqueda binario dado es")
    bst.inorder()
    bst.delete(25)
    print("Después de eliminar el nodo 25, el recorrido en orden es")
    bst.inorder()
    bst.insert(2)
    print("Después de insertar el nodo 2, el recorrido en orden es")
    bst.inorder()