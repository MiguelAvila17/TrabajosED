#include <iostream>
#define MAX_SIZE 100 // Tamaño máximo de la pila

int stack[MAX_SIZE];
int top = -1;

// Inserta elemento en la pila
void push(int item) {
    if (top == MAX_SIZE - 1) {
        std::cout << "Stack Overflow\n";
        return;
    }
    stack[++top] = item;
}

// Elimina y retorna el elemento superior
int pop() {
    if (top == -1) {
        std::cout << "Stack Underflow\n";
        return -1;
    }
    return stack[top--];
}

// Muestra el elemento superior sin eliminarlo
int peek() {
    if (top == -1) {
        std::cout << "Pila vacía\n";
        return -1;
    }
    return stack[top];
}

bool isEmpty() { return top == -1; }
bool isFull() { return top == MAX_SIZE - 1; }

int main() {
    push(10);
    push(20);
    push(30);

    std::cout << "Elemento Superior: " << peek() << "\n";
    std::cout << "Extrae elemento: " << pop() << "\n";
    std::cout << "Elemento Superior: " << peek() << "\n";

    return 0;
}