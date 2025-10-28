function Counting_Sort(arr) {
    if (arr.length === 0) return arr;

    let maxVal = Math.max(...arr);
    let count = new Array(maxVal + 1).fill(0);

    arr.forEach(num => count[num]++);

    let index = 0;
    for (let i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
    return arr;
}

// Ejemplo
let arr = [4, 2, 2, 8, 3, 3, 1];
console.log(countingSort(arr));