// 1. Recorrido
let arr = [10, 20, 30, 40, 50];
console.log("Recorrido del arreglo:");
arr.forEach(v => console.log(v));

// 2. Insertar en índice
arr.splice(2, 0, 99); // inserta 99 en la posición 2
console.log("Después de insertar:", arr);

// 3. Búsqueda lineal
let x = 30;
let encontrado = false;
for (let i = 0; i < arr.length; i++) {
    if (arr[i] === x) {
        console.log(`Elemento ${x} encontrado en índice ${i}`);
        encontrado = true;
        break;
    }
}
if (!encontrado)
    console.log(`Elemento ${x} no encontrado`);
