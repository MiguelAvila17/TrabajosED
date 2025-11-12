const MAXSIZE = 5;
let queue = [];

function insertar(e) {
    if (queue.length === MAXSIZE) return console.log("OVERFLOW");
    queue.push(e);
    queue.sort((a, b) => b - a);
    console.log("Insertado:", e);
}

function eliminar() {
    if (queue.length === 0) return console.log("UNDERFLOW");
    console.log("Eliminado:", queue.shift());
}

function mostrar() {
    console.log("Cola:", queue);
}

// Ejemplo
insertar(5); insertar(10); insertar(3);
mostrar();
eliminar();
mostrar();