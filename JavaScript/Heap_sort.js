// Ajustar un subárbol al heap máximo
function heapify(arr, n, i) {
    let largest = i;
    let left = 2 * i + 1;
    let right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest !== i) {
        [arr[i], arr[largest]] = [arr[largest], arr[i]]; // Intercambio
        heapify(arr, n, largest);
    }
}

// Implementación de Heapsort
function heapsort(arr) {
    let n = arr.length;

    // Construir heap máximo
    for (let i = Math.floor(n / 2) - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos
    for (let i = n - 1; i > 0; i--) {
        [arr[0], arr[i]] = [arr[i], arr[0]];
        heapify(arr, i, 0);
    }
}

// Ejemplo de uso
let arr = [12, 11, 13, 5, 6, 7];
console.log("Antes de ordenar:", arr);
heapsort(arr);
console.log("Después de ordenar:", arr);