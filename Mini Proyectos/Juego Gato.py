def imprimir_tablero(tablero):
    """Imprime el tablero de juego en la consola."""
    for i in range(3):
        print(f" {tablero[i][0]} | {tablero[i][1]} | {tablero[i][2]} ")
        if i < 2:
            print("---+---+---")

def imprimir_tablero_ejemplo():
    """Imprime el tablero de ejemplo con posiciones del 1 al 9."""
    print("TABLERO DE EJEMPLO (Guía de posiciones):")
    print(" 1 | 2 | 3 ")
    print("---+---+---")
    print(" 4 | 5 | 6 ")
    print("---+---+---")
    print(" 7 | 8 | 9 ")
    print()

def verificar_ganador(tablero, jugador):
    """Verifica si el jugador actual ha ganado."""
    # Verificar filas
    for i in range(3):
        if all([tablero[i][j] == jugador for j in range(3)]):
            return True
    # Verificar columnas
    for j in range(3):
        if all([tablero[i][j] == jugador for i in range(3)]):
            return True
    # Verificar diagonales
    if all([tablero[i][i] == jugador for i in range(3)]):
        return True
    if all([tablero[i][2-i] == jugador for i in range(3)]):
        return True
    return False

def juego_gato():
    """Función principal para ejecutar el juego del gato."""
    tablero = [[' ' for _ in range(3)] for _ in range(3)]
    jugador_actual = 'X'
    movimientos = 0

    print("¡Bienvenido al Juego del Gato!")
    print()
    imprimir_tablero_ejemplo()

    while True:
        print("TABLERO DEL JUEGO:")
        imprimir_tablero(tablero)
        print()
        print(f"Turno del jugador '{jugador_actual}'.")

        try:
            pos = int(input("Elige una posición (1-9): "))

            if not (1 <= pos <= 9):
                print("Posición inválida. ¡Intenta de nuevo!")
                continue

            # Convertir posición 1-9 a fila y columna
            fila = (pos - 1) // 3
            col = (pos - 1) % 3

            if tablero[fila][col] == ' ':
                tablero[fila][col] = jugador_actual
                movimientos += 1
            else:
                print("¡Esa casilla ya está ocupada! Elige otra.")
                continue

        except ValueError:
            print("Entrada inválida. Por favor, ingresa un número.")
            continue

        if verificar_ganador(tablero, jugador_actual):
            print()
            imprimir_tablero(tablero)
            print(f"🎉¡Felicidades!🎉 El jugador '{jugador_actual}' ha ganado.")
            break

        if movimientos == 9:
            print()
            imprimir_tablero(tablero)
            print("¡Es un empate! 🤝")
            break

        # Cambiar de jugador
        jugador_actual = 'O' if jugador_actual == 'X' else 'X'

# Iniciar el juego
if __name__ == "__main__":
    juego_gato()
