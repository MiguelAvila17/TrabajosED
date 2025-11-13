package Pilas.Con_Listas;

public class pila_lista {
    
}

class Node {
    int data;
    Node next;
    Node(int data) { this.data = data; this.next = null; }
}

class Stack {
    Node top = null;

    void push(int data) {
        Node newNode = new Node(data);
        newNode.next = top;
        top = newNode;
    }

    int pop() {
        if (top == null) {
            System.out.println("Pila vacía");
            return -1;
        }
        int val = top.data;
        top = top.next;
        return val;
    }

    int peek() {
        return (top == null) ? -1 : top.data;
    }

    void display() {
        Node temp = top;
        while (temp != null) {
            System.out.print(temp.data + " -> ");
            temp = temp.next;
        }
        System.out.println("null");
    }

    public static void main(String[] args) {
        Stack s = new Stack();
        s.push(10);
        s.push(20);
        s.push(30);
        s.display();
        s.pop();
        s.display();
    }
}