import readline from 'readline-sync';

class Nodo {
  constructor(dato) {
    this.dato = dato;
    this.anterior = null;
    this.siguiente = null;
  }
}

class ListaDobleCircular {
  constructor() {
    this.cabeza = null;
  }

  agregar(dato) {
    const nuevo = new Nodo(dato);
    if (!this.cabeza) {
      this.cabeza = nuevo;
      nuevo.siguiente = nuevo;
      nuevo.anterior = nuevo;
      return;
    }

    const ultimo = this.cabeza.anterior;
    ultimo.siguiente = nuevo;
    nuevo.anterior = ultimo;
    nuevo.siguiente = this.cabeza;
    this.cabeza.anterior = nuevo;
  }

  mostrar() {
    if (!this.cabeza) {
      console.log("Lista vacía.");
      return;
    }
    let actual = this.cabeza;
    process.stdout.write("Lista doble circular: ");
    do {
      process.stdout.write(actual.dato + " <-> ");
      actual = actual.siguiente;
    } while (actual !== this.cabeza);
    console.log("(vuelve al inicio)\n");
  }
}

const lista = new ListaDobleCircular();
let opcion;

do {
  console.log("=== LISTA DOBLE CIRCULAR (JavaScript) ===");
  console.log("1. Agregar nodo");
  console.log("2. Mostrar lista");
  console.log("3. Salir");
  opcion = readline.question("Opción: ");

  switch (opcion) {
    case "1":
      const dato = readline.questionInt("Dato: ");
      lista.agregar(dato);
      break;
    case "2":
      lista.mostrar();
      break;
  }
} while (opcion !== "3");