function selection(arr) {
    for (let i = 0; i < arr.length; i++) {
        let small = i;
        for (let j = i + 1; j < arr.length; j++) {
            if (arr[small] > arr[j]) {
                small = j;
            }
        }
        [arr[i], arr[small]] = [arr[small], arr[i]];
    }
}

function printArr(arr) {
    console.log(arr.join(" "));
}

// Generar arreglo aleatorio
let a = Array.from({ length: 5 }, () => Math.floor(Math.random() * 100) + 1);

console.log("Arreglo antes de ser ordenado:");
printArr(a);

selection(a);

console.log("\nArreglo después de ser ordenado:");
printArr(a);