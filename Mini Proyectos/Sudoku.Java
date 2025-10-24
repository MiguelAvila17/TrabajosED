import java.util.*;

public class Sudoku {
    private static final int SIZE = 9;
    private static int[][] board = new int[SIZE][SIZE];
    private static int[][] solution = new int[SIZE][SIZE];
    private static boolean[][] isOriginal = new boolean[SIZE][SIZE];
    private static boolean[][] isHint = new boolean[SIZE][SIZE];
    private static int hintsUsed = 0;

    private static Scanner sc = new Scanner(System.in);

    // Colores para consola (ANSI)
    private static final String RESET = "\u001B[0m";
    private static final String WHITE = "\u001B[37m";
    private static final String GREEN = "\u001B[32m";
    private static final String YELLOW = "\u001B[33m";

    public static void main(String[] args) {
        System.out.println("=== Bienvenido al Sudoku ===");
        System.out.println("Elige nivel: 1-Fácil  2-Medio  3-Difícil");
        int nivel = sc.nextInt();
        sc.nextLine();

        generateSudoku(nivel);

        while (true) {
            printBoard();
            System.out.println("Opciones: ");
            System.out.println("1-Insertar número  2-Pedir pista  3-Salir");
            int opcion = sc.nextInt();
            sc.nextLine();

            switch (opcion) {
                case 1:
                    insertarNumero();
                    if (isSolved()) {
                        printBoard();
                        System.out.println("¡Felicidades! Has completado el Sudoku.");
                        return;
                    }
                    break;
                case 2:
                    darPista();
                    break;
                case 3:
                    System.out.println("Gracias por jugar.");
                    return;
                default:
                    System.out.println("Opción inválida.");
            }
        }
    }

    private static void generateSudoku(int nivel) {
        fillBoard(solution);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = solution[i][j];
                isOriginal[i][j] = true;
            }
        }

        int holes = 0;
        switch (nivel) {
            case 1: holes = 35; break;
            case 2: holes = 45; break;
            case 3: holes = 55; break;
        }

        Random rand = new Random();
        for (int i = 0; i < holes; i++) {
            int row, col;
            do {
                row = rand.nextInt(SIZE);
                col = rand.nextInt(SIZE);
            } while (board[row][col] == 0);
            board[row][col] = 0;
            isOriginal[row][col] = false;
        }
    }

    private static boolean fillBoard(int[][] grid) {
        List<Integer> nums = new ArrayList<>();
        for (int i = 1; i <= SIZE; i++) nums.add(i);
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    Collections.shuffle(nums);
                    for (int num : nums) {
                        if (isSafe(grid, row, col, num)) {
                            grid[row][col] = num;
                            if (fillBoard(grid)) return true;
                            grid[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    private static boolean isSafe(int[][] grid, int row, int col, int num) {
        for (int i = 0; i < SIZE; i++) {
            if (grid[row][i] == num || grid[i][col] == num) return false;
        }
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (grid[i][j] == num) return false;
            }
        }
        return true;
    }

    private static void printBoard() {
        System.out.println("\nTablero:");
        System.out.println("╔═══════╦═══════╦═══════╗");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0) System.out.print("║ ");
                if (board[i][j] == 0) {
                    System.out.print(". ");
                } else if (isOriginal[i][j]) {
                    System.out.print(WHITE + board[i][j] + RESET + " ");
                } else if (isHint[i][j]) {
                    System.out.print(YELLOW + board[i][j] + RESET + " ");
                } else {
                    System.out.print(GREEN + board[i][j] + RESET + " ");
                }
            }
            System.out.println("║");
            if (i == 2 || i == 5) {
                System.out.println("╠═══════╬═══════╬═══════╣");
            }
        }
        System.out.println("╚═══════╩═══════╩═══════╝");
        System.out.println("Pistas usadas: " + hintsUsed + "/3");
    }

    private static void insertarNumero() {
        System.out.println("Ingrese fila (1-9):");
        int row = sc.nextInt() - 1;
        System.out.println("Ingrese columna (1-9):");
        int col = sc.nextInt() - 1;
        System.out.println("Ingrese número (1-9):");
        int num = sc.nextInt();

        if (isOriginal[row][col]) {
            System.out.println("No puedes cambiar un número original.");
        } else {
            if (isSafe(board, row, col, num)) {
                board[row][col] = num;
                isHint[row][col] = false;
            } else {
                System.out.println("Número no permitido en esta posición.");
            }
        }
    }

    private static void darPista() {
        if (hintsUsed >= 3) {
            System.out.println("Ya has usado las 3 pistas.");
            return;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = solution[i][j];
                    isHint[i][j] = true;
                    hintsUsed++;
                    System.out.println("Pista usada en fila " + (i + 1) + " columna " + (j + 1));
                    return;
                }
            }
        }
        System.out.println("No hay más casillas vacías para dar pista.");
    }

    private static boolean isSolved() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] != solution[i][j]) return false;
        return true;
    }
}