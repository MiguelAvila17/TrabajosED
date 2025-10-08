function hashSort(arr) {
    let hashTable = {};
    let maxVal = 0;

    for (let num of arr) {
        hashTable[num] = (hashTable[num] || 0) + 1;
        if (num > maxVal) maxVal = num;
    }

    let sortedArr = [];
    for (let i = 0; i <= maxVal; i++) {
        if (hashTable[i]) {
            for (let j = 0; j < hashTable[i]; j++) {
                sortedArr.push(i);
            }
        }
    }
    return sortedArr;
}

let arr = [4, 2, 2, 8, 3, 3, 1];
console.log("Arreglo original:", arr);

let sortedArr = hashSort(arr);
console.log("Arreglo ordenado:", sortedArr);