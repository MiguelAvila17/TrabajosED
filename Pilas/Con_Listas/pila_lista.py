class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        self.top = None

    def push(self, data):
        new_node = Node(data)
        new_node.next = self.top
        self.top = new_node

    def pop(self):
        if self.top is None:
            print("Pila vacía")
            return None
        data = self.top.data
        self.top = self.top.next
        return data

    def peek(self):
        return None if self.top is None else self.top.data

    def display(self):
        temp = self.top
        while temp:
            print(temp.data, "->", end=" ")
            temp = temp.next
        print("None")

# Ejemplo
p = Stack()
p.push(10)
p.push(20)
p.push(30)
p.display()
p.pop()
p.display()