const MAXSIZE = 5;
let queue = new Array(MAXSIZE);
let front = -1, rear = -1;

function insertar(elemento) {
    if (rear === MAXSIZE - 1) return console.log("OVERFLOW");
    if (front === -1 && rear === -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    queue[rear] = elemento;
    console.log("Insertado:", elemento);
}

function eliminar() {
    if (front === -1 || front > rear) return console.log("UNDERFLOW");
    console.log("Eliminado:", queue[front]);
    if (front === rear) front = rear = -1;
    else front++;
}

function mostrar() {
    if (front === -1 || front > rear) return console.log("Vacía");
    console.log("Cola:", queue.slice(front, rear + 1));
}

// Ejemplo de uso
insertar(10);
insertar(20);
mostrar();
eliminar();
mostrar();