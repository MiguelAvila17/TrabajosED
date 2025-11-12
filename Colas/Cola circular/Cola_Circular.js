const MAXSIZE = 5;
let queue = new Array(MAXSIZE).fill(null);
let front = -1, rear = -1;

function estaVacia() { return front === -1; }
function estaLlena() { return (rear + 1) % MAXSIZE === front; }

function insertar(elemento) {
    if (estaLlena()) return console.log("OVERFLOW");
    if (estaVacia()) front = rear = 0;
    else rear = (rear + 1) % MAXSIZE;
    queue[rear] = elemento;
    console.log("Insertado:", elemento);
}

function eliminar() {
    if (estaVacia()) return console.log("UNDERFLOW");
    console.log("Eliminado:", queue[front]);
    if (front === rear) front = rear = -1;
    else front = (front + 1) % MAXSIZE;
}

function mostrar() {
    if (estaVacia()) return console.log("Vacía");
    let i = front, res = [];
    while (true) {
        res.push(queue[i]);
        if (i === rear) break;
        i = (i + 1) % MAXSIZE;
    }
    console.log("Cola:", res.join(" "));
}

// Ejemplo de uso:
insertar(10); insertar(20); insertar(30);
mostrar();
eliminar();
mostrar();