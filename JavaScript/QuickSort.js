// Función para intercambiar dos elementos en el arreglo 
function swap(a, j, k) { // intercambia los elementos
    let temp = a[j];
    a[j] = a[k];
    a[k] = temp;
}

// Función para hacer la partición del arreglo 
function partition(a, l, h) {
    let pvt = a[h]; // Selecciona el pivote
    let j = l - 1;  // índice de los elementos menores
    for (let k = l; k < h; k++) { // recorre el arreglo
        if (a[k] < pvt) { // Si el elemento actual es menor que el pivote
            j++;
            swap(a, j, k);
        }
    }
    swap(a, j + 1, h); // coloca el pivote en su posición correcta
    return j + 1;
}

// Implementación de la función QuickSort 
function qckSort(a, l, h) {
    if (l < h) {
        let pi = partition(a, l, h);
        qckSort(a, l, pi - 1);
        qckSort(a, pi + 1, h);
    }
}

// Código principal para probar QuickSort 
let a = [10, 7, 8, 9, 1, 5]; // arreglo desordenado
console.log("El arreglo antes de ordenarlo:");
console.log(a.join(" "));

qckSort(a, 0, a.length - 1);

console.log("El arreglo después de ordenarlo:");
console.log(a.join(" "));