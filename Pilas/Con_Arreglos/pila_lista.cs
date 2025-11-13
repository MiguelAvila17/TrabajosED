using System;

class StackArray {
    const int MAX_SIZE = 100;
    static int[] stack = new int[MAX_SIZE];
    static int top = -1;

    static void Push(int item) {
        if (top == MAX_SIZE - 1) {
            Console.WriteLine("Stack Overflow");
            return;
        }
        stack[++top] = item;
    }

    static int Pop() {
        if (top == -1) {
            Console.WriteLine("Stack Underflow");
            return -1;
        }
        return stack[top--];
    }

    static int Peek() {
        if (top == -1) {
            Console.WriteLine("Pila vacía");
            return -1;
        }
        return stack[top];
    }

    static bool IsEmpty() => top == -1;
    static bool IsFull() => top == MAX_SIZE - 1;

    static void Main() {
        Push(10);
        Push(20);
        Push(30);

        Console.WriteLine("Elemento Superior: " + Peek());
        Console.WriteLine("Extrae elemento: " + Pop());
        Console.WriteLine("Elemento Superior: " + Peek());
    }
}