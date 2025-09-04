let matriz = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
];

console.log("Recorrido por renglones:");
for(let i=0; i<matriz.length; i++) {
    let fila = "";
    for(let j=0; j<matriz[i].length; j++) {
        fila += matriz[i][j] + " ";
    }
    console.log(fila);
}

console.log("\nRecorrido por columnas:");
for(let j=0; j<matriz[0].length; j++) {
    let col = "";
    for(let i=0; i<matriz.length; i++) {
        col += matriz[i][j] + " ";
    }
    console.log(col);
}