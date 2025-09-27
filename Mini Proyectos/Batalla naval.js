// batalla_naval_mejorado.js

//Revisado Primera Parte 26/09/2025

const readline = require('readline');

const FILAS = 10;
const COLUMNAS = 10;
const VACIO = '.';
const TOCADO = 'X';
const AGUA = '·';
const LETRAS = 'ABCDEFGHIJ';

function crearTablero() {
    return Array.from({ length: FILAS }, () => Array(COLUMNAS).fill(VACIO));
}

function imprimirTablero(tablero, ocultarBarcos = false) {
    console.log('  ' + Array.from({ length: COLUMNAS }, (_, i) => i + 1).join(' '));
    for (let i = 0; i < FILAS; i++) {
        let fila = LETRAS[i] + ' ';
        for (let j = 0; j < COLUMNAS; j++) {
            if (ocultarBarcos && tablero[i][j] === 'B') fila += VACIO + ' ';
            else fila += tablero[i][j] + ' ';
        }
        console.log(fila);
    }
}

function parsearJugada(input) {
    input = input.toUpperCase();
    const fila = LETRAS.indexOf(input[0]);
    const col = parseInt(input.slice(1)) - 1;
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) return null;
    return [fila, col];
}

async function colocarBarco(rl, tablero, jugador, numeroBarco) {
    while (true) {
        imprimirTablero(tablero);
        console.log(`\n${jugador}, coloca tu barco #${numeroBarco}`);
        const tamañoEntrada = await new Promise(res => rl.question('Elige tamaño del barco (2, 3 o 4): ', res));
        const tamaño = parseInt(tamañoEntrada);
        if (![2,3,4].includes(tamaño)) { console.log('Tamaño inválido.'); continue; }

        const entrada = await new Promise(res => rl.question('Coordenada inicial (Ej: A1): ', res));
        const inicio = parsearJugada(entrada);
        if (!inicio) { console.log('Coordenada inválida.'); continue; }

        const orientacion = await new Promise(res => rl.question('Horizontal (H) o Vertical (V)? ', res));
        const fila = inicio[0];
        const col = inicio[1];

        let celdas = [];
        if (orientacion.toUpperCase() === 'H') {
            if (col + tamaño - 1 >= COLUMNAS) { console.log('No cabe horizontalmente.'); continue; }
            for (let i = 0; i < tamaño; i++) celdas.push([fila, col + i]);
        } else if (orientacion.toUpperCase() === 'V') {
            if (fila + tamaño - 1 >= FILAS) { console.log('No cabe verticalmente.'); continue; }
            for (let i = 0; i < tamaño; i++) celdas.push([fila + i, col]);
        } else { console.log('Orientación inválida.'); continue; }

        if (celdas.some(([r, c]) => tablero[r][c] === 'B')) {
            console.log('Ya hay un barco ahí.');
            continue;
        }

        for (const [r, c] of celdas) tablero[r][c] = 'B';
        break;
    }
}

function disparar(tablero, fila, col) {
    if (tablero[fila][col] === 'B') { tablero[fila][col] = TOCADO; return true; }
    else if (tablero[fila][col] === VACIO) { tablero[fila][col] = AGUA; return false; }
    return null; // ya disparado
}

function todosHundidos(tablero) {
    return !tablero.some(fila => fila.includes('B'));
}

async function main() {
    const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

    const tablero1 = crearTablero();
    const tablero2 = crearTablero();

    console.log('Jugador 1, coloca tus 4 barcos uno por uno.');
    for (let i = 0; i < 4; i++) await colocarBarco(rl, tablero1, 'Jugador 1', i+1);
    console.clear();

    console.log('Jugador 2, coloca tus 4 barcos uno por uno.');
    for (let i = 0; i < 4; i++) await colocarBarco(rl, tablero2, 'Jugador 2', i+1);
    console.clear();

    let turno = 1;
    while (true) {
        console.log(`\nTurno del Jugador ${turno}`);
        const tableroOponente = turno === 1 ? tablero2 : tablero1;
        const tableroJugador = turno === 1 ? tablero1 : tablero2;

        console.log('\nTu tablero:');
        imprimirTablero(tableroJugador);

        console.log('\nTablero del oponente:');
        imprimirTablero(tableroOponente, true);

        const entrada = await new Promise(res => rl.question('Dispara a una coordenada (Ej: A1): ', res));
        const jugada = parsearJugada(entrada);
        if (!jugada) { console.log('Coordenada inválida.'); continue; }

        const [fila, col] = jugada;
        const resultado = disparar(tableroOponente, fila, col);

        if (resultado === true) console.log('¡TOCADO!');
        else if (resultado === false) console.log('¡AGUA!');
        else { console.log('Ya disparaste ahí.'); continue; }

        if (todosHundidos(tableroOponente)) {
            console.log(`\n¡Jugador ${turno} gana!`);
            imprimirTablero(tableroOponente);
            break;
        }

        turno = turno === 1 ? 2 : 1;
    }

    rl.close();
}

main();