using System;

class Node {
    public int Data;
    public Node Next;
    public Node(int data) { Data = data; Next = null; }
}

class Stack {
    private Node top;

    public void Push(int data) {
        Node newNode = new Node(data);
        newNode.Next = top;
        top = newNode;
    }

    public int Pop() {
        if (top == null) {
            Console.WriteLine("Pila vacía");
            return -1;
        }
        int value = top.Data;
        top = top.Next;
        return value;
    }

    public int Peek() => top == null ? -1 : top.Data;

    public void Display() {
        Node temp = top;
        while (temp != null) {
            Console.Write(temp.Data + " -> ");
            temp = temp.Next;
        }
        Console.WriteLine("null");
    }

    static void Main() {
        Stack pila = new Stack();
        pila.Push(10);
        pila.Push(20);
        pila.Push(30);
        pila.Display();
        pila.Pop();
        pila.Display();
    }
}