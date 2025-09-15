#include <iostream>
#include <vector>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;

// Colores
const string RESET   = "\033[0m";
const string ROJO    = "\033[31m";
const string AMARILLO= "\033[33m";

// Imprimir tablero con colores
void imprimirTablero(const vector<vector<char>>& tablero) {
    system("clear");
cout << "\n====CONECTA 4====\n";
    for (int i = 0; i < FILAS; i++) {
        cout << "| ";
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == 'X') {
                cout << ROJO << "X " << RESET;
            } else if (tablero[i][j] == 'O') {
                cout << AMARILLO << "O " << RESET;
            } else {
                cout << ". ";
            }
        }
        cout << "|\n";
    }
    cout << "  ";
    for (int j = 1; j <= COLUMNAS; j++) cout << j << " ";
    cout << "\n";
}

// Colocar ficha en columna
bool colocarFicha(vector<vector<char>>& tablero, int columna, char ficha) {
    if (columna < 0 || columna >= COLUMNAS) return false;
    for (int i = FILAS - 1; i >= 0; i--) {
        if (tablero[i][columna] == '.') {
            tablero[i][columna] = ficha;
            return true;
        }
    }
    return false;
}

// Verificar ganador
bool hayGanador(const vector<vector<char>>& tablero, char ficha) {
    // Horizontal
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS - 3; j++)
            if (tablero[i][j] == ficha && tablero[i][j+1] == ficha &&
                tablero[i][j+2] == ficha && tablero[i][j+3] == ficha)
                return true;

    // Vertical
    for (int i = 0; i < FILAS - 3; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (tablero[i][j] == ficha && tablero[i+1][j] == ficha &&
                tablero[i+2][j] == ficha && tablero[i+3][j] == ficha)
                return true;

    for (int i = 0; i < FILAS - 3; i++)
        for (int j = 0; j < COLUMNAS - 3; j++)
            if (tablero[i][j] == ficha && tablero[i+1][j+1] == ficha &&
                tablero[i+2][j+2] == ficha && tablero[i+3][j+3] == ficha)
                return true;

    for (int i = 3; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS - 3; j++)
            if (tablero[i][j] == ficha && tablero[i-1][j+1] == ficha &&
                tablero[i-2][j+2] == ficha && tablero[i-3][j+3] == ficha)
                return true;

    return false;
}

int main() {
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, '.'));

    char jugador1 = 'X', jugador2 = 'O';
    bool turnoJugador1 = true;
    int movimientos = 0;

    while (true) {
        imprimirTablero(tablero);
        int columna;
        if (turnoJugador1) {
            cout << ROJO << "Turno Jugador 1 (X - Rojo). Elige columna (1-7): " << RESET;
        } else {
            cout << AMARILLO << "Turno Jugador 2 (O - Amarillo). Elige columna (1-7): " << RESET;
        }
        cin >> columna;
        columna--; // Ajustar a índice

        if (!colocarFicha(tablero, columna, turnoJugador1 ? jugador1 : jugador2)) {
            cout << "Columna inválida o llena. Intenta de nuevo.\n";
            cin.ignore();
            cin.get();
            continue;
        }

        movimientos++;
        if (hayGanador(tablero, turnoJugador1 ? jugador1 : jugador2)) {
            imprimirTablero(tablero);
            if (turnoJugador1) {
                cout << ROJO << "\n¡¡Jugador 1 (Rojo) gana!!\n" << RESET;
            } else {
                cout << AMARILLO << "\n¡¡Jugador 2 (Amarillo) gana!!\n" << RESET;
            }
            break;
        }

        if (movimientos == FILAS * COLUMNAS) {
            imprimirTablero(tablero);
            cout << "\nEmpate, tablero lleno.\n";
            break;
        }

        turnoJugador1 = !turnoJugador1;
    }

    return 0;
}
