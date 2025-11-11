import readlineSync from "readline-sync";

class Nodo {
  dato: number;
  siguiente: Nodo | null;

  constructor(dato: number) {
    this.dato = dato;
    this.siguiente = null;
  }
}

class ListaCircular {
  private cabeza: Nodo | null = null;

  agregar(dato: number): void {
    const nuevo = new Nodo(dato);

    if (!this.cabeza) {
      this.cabeza = nuevo;
      nuevo.siguiente = this.cabeza;
      return;
    }

    let actual = this.cabeza;
    while (actual.siguiente !== this.cabeza) {
      actual = actual.siguiente!;
    }

    actual.siguiente = nuevo;
    nuevo.siguiente = this.cabeza;
  }

  mostrar(): void {
    if (!this.cabeza) {
      console.log("Lista vacía.\n");
      return;
    }

    let actual = this.cabeza;
    process.stdout.write("\nLista circular: ");
    do {
      process.stdout.write(actual.dato + " -> ");
      actual = actual.siguiente!;
    } while (actual !== this.cabeza);
    console.log("(vuelve al inicio)\n");
  }
}

// Programa principal
const lista = new ListaCircular();
let opcion = 0;

do {
  console.log("=== LISTA ENLAZADA CIRCULAR (TypeScript) ===");
  console.log("1. Agregar nodo");
  console.log("2. Mostrar lista");
  console.log("3. Salir");
  opcion = parseInt(readlineSync.question("Opción: "));

  switch (opcion) {
    case 1:
      const dato = parseInt(readlineSync.question("Dato: "));
      lista.agregar(dato);
      break;
    case 2:
      lista.mostrar();
      break;
  }
} while (opcion !== 3);