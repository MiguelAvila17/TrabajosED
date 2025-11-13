class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class Stack {
  constructor() {
    this.top = null;
  }

  push(data) {
    const node = new Node(data);
    node.next = this.top;
    this.top = node;
  }

  pop() {
    if (!this.top) {
      console.log("Pila vacía");
      return null;
    }
    const value = this.top.data;
    this.top = this.top.next;
    return value;
  }

  peek() {
    return this.top ? this.top.data : null;
  }

  isEmpty() {
    return this.top === null;
  }

  display() {
    let current = this.top;
    let out = "";
    while (current) {
      out += current.data + " -> ";
      current = current.next;
    }
    console.log(out + "null");
  }
}

// Ejemplo
const pila = new Stack();
pila.push(10);
pila.push(20);
pila.push(30);
pila.display();
pila.pop();
pila.display();