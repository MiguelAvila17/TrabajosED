function burbuja(arr) {
    let n = arr.length;
    for (let i = 0; i < n - 1; i++) {
        for (let j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                let temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Generar arreglo de 10 números aleatorios entre 1 y 100
let arr = Array.from({length: 10}, () => Math.floor(Math.random() * 100) + 1);

console.log("Original:", arr);
burbuja(arr);
console.log("Ordenado:", arr);