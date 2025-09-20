const SIZE = 5;
const BARCOS = 3;

let tablero1 = [];
let tablero2 = [];
let barcos1 = [];
let barcos2 = [];
let turno = 1;
let colocando = true;
let barcosColocados = 0;

const tableroDiv1 = document.getElementById("tablero1");
const tableroDiv2 = document.getElementById("tablero2");
const mensaje = document.getElementById("mensaje");
const btnReiniciar = document.getElementById("reiniciar");

function crearTableroHTML(tableroDiv, jugador) {
  tableroDiv.innerHTML = "";
  for (let fila = 0; fila < SIZE; fila++) {
    for (let col = 0; col < SIZE; col++) {
      const celda = document.createElement("div");
      celda.classList.add("celda");
      celda.dataset.fila = fila;
      celda.dataset.col = col;
      celda.dataset.jugador = jugador;

      celda.addEventListener("click", () => manejarClick(celda));
      tableroDiv.appendChild(celda);
    }
  }
}

function inicializar() {
  tablero1 = Array.from({ length: SIZE }, () => Array(SIZE).fill("-"));
  tablero2 = Array.from({ length: SIZE }, () => Array(SIZE).fill("-"));
  barcos1 = Array.from({ length: SIZE }, () => Array(SIZE).fill(false));
  barcos2 = Array.from({ length: SIZE }, () => Array(SIZE).fill(false));

  turno = 1;
  colocando = true;
  barcosColocados = 0;
  mensaje.textContent = "Colocación de barcos: Jugador 1";

  crearTableroHTML(tableroDiv1, 1);
  crearTableroHTML(tableroDiv2, 2);
}

function manejarClick(celda) {
  let fila = parseInt(celda.dataset.fila);
  let col = parseInt(celda.dataset.col);
  let jugador = parseInt(celda.dataset.jugador);

  if (colocando) {
    colocarBarco(fila, col, jugador, celda);
  } else {
    disparar(fila, col, jugador, celda);
  }
}

function colocarBarco(fila, col, jugador, celda) {
  let barcos = jugador === 1 ? barcos1 : barcos2;

  if (barcos[fila][col]) return;

  barcos[fila][col] = true;
  celda.classList.add("barco");
  barcosColocados++;

  if (barcosColocados === BARCOS) {
    if (jugador === 1) {
      mensaje.textContent = "Colocación de barcos: Jugador 2";
      barcosColocados = 0;
    } else {
      colocando = false;
      mensaje.textContent = "Turno de Jugador 1";
    }
  }
}

function disparar(fila, col, jugador, celda) {
  if ((jugador === 1 && turno === 1) || (jugador === 2 && turno === 2)) {
    return; // no puedes disparar a tu propio tablero
  }

  let tablero = turno === 1 ? tablero2 : tablero1;
  let barcos = turno === 1 ? barcos2 : barcos1;

  if (tablero[fila][col] !== "-") return;

  if (barcos[fila][col]) {
    celda.classList.add("tocado");
    tablero[fila][col] = "X";
    barcos[fila][col] = false;
    if (!quedanBarcos(barcos)) {
      mensaje.textContent = `¡Jugador ${turno} gana! 🎉`;
      colocando = true; // desactiva el juego
      return;
    }
  } else {
    celda.classList.add("agua");
    tablero[fila][col] = "O";
    turno = turno === 1 ? 2 : 1;
    mensaje.textContent = `Turno de Jugador ${turno}`;
  }
}

function quedanBarcos(barcos) {
  return barcos.some(row => row.some(cell => cell));
}

btnReiniciar.addEventListener("click", inicializar);

inicializar();