function insertionSort(bukt) {
  for (let j = 1; j < bukt.length; j++) {
    let val = bukt[j];
    let k = j - 1;
    while (k >= 0 && bukt[k] > val) {
      bukt[k + 1] = bukt[k];
      k--;
    }
    bukt[k + 1] = val;
  }
}

function bucketSort(arr) {
  let s = arr.length;
  let buckets = Array.from({ length: s }, () => []);

  for (let num of arr) {
    let bi = Math.floor(s * num);
    if (bi >= s) bi = s - 1;
    buckets[bi].push(num);
  }

  for (let b of buckets) insertionSort(b);

  let idx = 0;
  for (let b of buckets)
    for (let num of b)
      arr[idx++] = num;
}

// Ejemplo de uso
let inputArr = [0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67];
console.log("Arreglo antes de ordenar:");
console.log(inputArr.join(" "));
bucketSort(inputArr);
console.log("Arreglo después de ordenar:");
console.log(inputArr.join(" "));