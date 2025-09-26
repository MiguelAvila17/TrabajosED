// Merge dos subarrays de a[].
function merge(a, l, m, r) {
    let a1 = m - l + 1; // Tamaño del primer subarray
    let a2 = r - m;     // Tamaño del segundo subarray

    // Crear arrays temporales
    let L = new Array(a1); // Crear array temporal
    let R = new Array(a2); // Crear array temporal

    // Copiar datos a los arrays temporales L[] y R[]
    for (let j = 0; j < a1; j++) // copiar datos al array temporal
        L[j] = a[l + j];
    for (let k = 0; k < a2; k++) // copiar datos al array temporal
        R[k] = a[m + 1 + k];

    let i = 0; // Indice inicial del primer subarray
    let j2 = 0; // Indice inicial del segundo subarray
    let k2 = l; // Indice inicial del subarray mezclado

    // Mezclar los arrays temporales de nuevo en a[l..r]
    while (i < a1 && j2 < a2) { // recorrer ambos arrays
        if (L[i] <= R[j2]) {    // comparar los elementos de ambos arrays
            a[k2] = L[i];       // copiar el elemento más pequeño al array original
            i = i + 1;          // incrementar el índice del primer array
        } else {                // si el elemento del segundo array es más pequeño
            a[k2] = R[j2];      // copiar el elemento al array original
            j2 = j2 + 1;        // incrementar el índice del segundo array
        }
        k2 = k2 + 1;            // incrementar el índice del array original
    }

    // copiar los elementos restantes de L[], si hay alguno
    while (i < a1) { // copiar los elementos restantes del primer array
        a[k2] = L[i]; // copiar el elemento al array original
        i = i + 1;    // incrementar el índice del primer array
        k2 = k2 + 1;  // incrementar el índice del array original
    }

    // copiar los elementos restantes de R[], si hay alguno
    while (j2 < a2) { // copiar los elementos restantes del segundo array
        a[k2] = R[j2]; // copiar el elemento al array original
        j2 = j2 + 1;   // incrementar el índice del segundo array
        k2 = k2 + 1;   // incrementar el índice del array original
    }
}

// función principal que ordena a[l..r]
function mergeSort(a, l, r) {
    if (l < r) {
        // Igual que (l + r)//2, pero evita el desbordamiento
        let m = Math.floor(l + (r - l) / 2);

        // Ordenar la primera y segunda mitad
        mergeSort(a, l, m);     // ordenar la primera mitad
        mergeSort(a, m + 1, r); // ordenar la segunda mitad
        merge(a, l, m, r);      // mezclar las dos mitades
    }
}

// Código para probar la implementación de MergeSort
let a = [39, 28, 44, 11]; // arreglo desordenado
let s = a.length; // tamaño del arreglo

console.log("Antes de ordenar el arreglo: ");
console.log(a.join(" "));

mergeSort(a, 0, s - 1); // llama a la función mergeSort

console.log("Después de ordenar el arreglo: ");
console.log(a.join(" "));