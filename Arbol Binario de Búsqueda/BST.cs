using System;

// Clase para representar un nodo
public class NodeBST
{
    public int data;
    public NodeBST leftNode;
    public NodeBST rightNode;

    public NodeBST(int data)
    {
        this.data = data;
        this.leftNode = null;
        this.rightNode = null;
    }
}

public class BinarySearchTree
{
    public NodeBST rootNode;

    public BinarySearchTree()
    {
        this.rootNode = null;
    }

    // Método de ayuda para encontrar el valor mínimo (sucesor inorden)
    private NodeBST FindMin(NodeBST node)
    {
        while (node.leftNode != null)
        {
            node = node.leftNode;
        }
        return node;
    }

    // --- INSERCIÓN ---
    public void Insert(int data)
    {
        rootNode = InsertRec(rootNode, data);
    }

    private NodeBST InsertRec(NodeBST currentNode, int data)
    {
        if (currentNode == null)
        {
            return new NodeBST(data);
        }

        if (data < currentNode.data)
        {
            currentNode.leftNode = InsertRec(currentNode.leftNode, data);
        }
        else if (data > currentNode.data)
        {
            currentNode.rightNode = InsertRec(currentNode.rightNode, data);
        }
        
        return currentNode;
    }

    // --- ELIMINACIÓN ---
    public void Delete(int data)
    {
        rootNode = DeleteRec(rootNode, data);
    }

    private NodeBST DeleteRec(NodeBST currentNode, int data)
    {
        if (currentNode == null)
        {
            return null;
        }

        if (data < currentNode.data)
        {
            currentNode.leftNode = DeleteRec(currentNode.leftNode, data);
        }
        else if (data > currentNode.data)
        {
            currentNode.rightNode = DeleteRec(currentNode.rightNode, data);
        }
        else // Nodo encontrado
        {
            // Caso 1 y 2: 0 o 1 hijo
            if (currentNode.leftNode == null)
            {
                return currentNode.rightNode;
            }
            if (currentNode.rightNode == null)
            {
                return currentNode.leftNode;
            }

            // Caso 3: Dos hijos
            NodeBST successor = FindMin(currentNode.rightNode);
            currentNode.data = successor.data; 
            currentNode.rightNode = DeleteRec(currentNode.rightNode, successor.data); 
        }

        return currentNode;
    }

    // --- RECORRIDO INORDEN ---
    public void Inorder()
    {
        InorderRec(rootNode);
        Console.WriteLine();
    }

    private void InorderRec(NodeBST node)
    {
        if (node != null)
        {
            InorderRec(node.leftNode);
            Console.Write(node.data + " ");
            InorderRec(node.rightNode);
        }
    }
}

/*
// Ejemplo de uso:
public class Program
{
    public static void Main(string[] args)
    {
        BinarySearchTree bst = new BinarySearchTree();
        // ... (Insertar y usar métodos)
    }
}
*/