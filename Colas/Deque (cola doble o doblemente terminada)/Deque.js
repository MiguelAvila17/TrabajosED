const MAXSIZE = 5;
let dequeArr = [];

function insertarFrente(e) {
    if (dequeArr.length === MAXSIZE) return console.log("OVERFLOW");
    dequeArr.unshift(e);
    console.log("Insertado al frente:", e);
}
function insertarFinal(e) {
    if (dequeArr.length === MAXSIZE) return console.log("OVERFLOW");
    dequeArr.push(e);
    console.log("Insertado al final:", e);
}
function eliminarFrente() {
    if (!dequeArr.length) return console.log("UNDERFLOW");
    console.log("Eliminado del frente:", dequeArr.shift());
}
function eliminarFinal() {
    if (!dequeArr.length) return console.log("UNDERFLOW");
    console.log("Eliminado del final:", dequeArr.pop());
}
function mostrar() {
    console.log("Deque:", dequeArr);
}

// Ejemplo:
insertarFinal(1); insertarFinal(2); insertarFrente(0);
mostrar();
eliminarFinal();
mostrar();