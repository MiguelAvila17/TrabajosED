import java.util.*;

public class Sudoku {

    private static final int SIZE = 9;
    private static int[][] board = new int[SIZE][SIZE];
    private static int[][] solution = new int[SIZE][SIZE];
    private static boolean[][] isOriginal = new boolean[SIZE][SIZE];
    private static boolean[][] isHint = new boolean[SIZE][SIZE];
    private static int hintsUsed = 0;
    private static final int MAX_HINTS = 3;
    private static Scanner sc = new Scanner(System.in);

    // Colores ANSI
    public static final String RESET = "\u001B[0m";
    public static final String RED = "\u001B[31m";
    public static final String GREEN = "\u001B[32m";
    public static final String BLUE = "\u001B[34m";

    public static void main(String[] args) {
        generateSudoku("facil"); // cambiar "medio" o "dificil"
        copyBoard(board, solution);
        int choice;
        do {
            displayBoard();
            System.out.println("1. Resolver Sudoku");
            System.out.println("2. Pedir pista (" + hintsUsed + "/" + MAX_HINTS + ")");
            System.out.println("3. Ingresar número");
            System.out.println("4. Limpiar Sudoku");
            System.out.println("0. Salir");
            System.out.print("Elige una opción: ");
            choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1 -> {
                    if (solve(board)) {
                        System.out.println(GREEN + "Sudoku resuelto correctamente!" + RESET);
                        displayBoard();
                    } else {
                        System.out.println(RED + "No tiene solución válida." + RESET);
                    }
                }
                case 2 -> giveHint();
                case 3 -> inputNumber();
                case 4 -> clearBoard();
            }
        } while (choice != 0);
    }

    private static void displayBoard() {
        System.out.println("\n╔═══════╦═══════╦═══════╗");
        for (int r = 0; r < SIZE; r++) {
            System.out.print("║ ");
            for (int c = 0; c < SIZE; c++) {
                String val = board[r][c] == 0 ? "." : String.valueOf(board[r][c]);
                if (board[r][c] != 0) {
                    if (isOriginal[r][c])
                        val = BLUE + val + RESET;
                    else if (isHint[r][c])
                        val = GREEN + val + RESET;
                    else if (!isValid(board, r, c, board[r][c]))
                        val = RED + val + RESET;
                }
                System.out.print(val + " ");
                if ((c + 1) % 3 == 0) System.out.print("║ ");
            }
            System.out.println();
            if ((r + 1) % 3 == 0 && r != SIZE - 1)
                System.out.println("╠═══════╬═══════╬═══════╣");
        }
        System.out.println("╚═══════╩═══════╩═══════╝\n");
    }

    private static void inputNumber() {
        System.out.print("Fila (1-9): ");
        int r = sc.nextInt() - 1;
        System.out.print("Columna (1-9): ");
        int c = sc.nextInt() - 1;

        if (isOriginal[r][c] || isHint[r][c]) {
            System.out.println(RED + "No puedes modificar esta celda." + RESET);
            return;
        }

        System.out.print("Número (1-9): ");
        int num = sc.nextInt();
        if (num < 1 || num > 9) {
            System.out.println(RED + "Número inválido." + RESET);
            return;
        }

        if (isValid(board, r, c, num)) {
            board[r][c] = num;
            System.out.println(GREEN + "Número colocado correctamente." + RESET);
        } else {
            board[r][c] = num;
            System.out.println(RED + "Número colocado, pero genera conflicto." + RESET);
        }
    }

    private static void giveHint() {
        if (hintsUsed >= MAX_HINTS) {
            System.out.println(RED + "Ya usaste todas las pistas disponibles." + RESET);
            return;
        }
        List<int[]> emptyCells = new ArrayList<>();
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                if (board[r][c] == 0)
                    emptyCells.add(new int[]{r, c});

        if (emptyCells.isEmpty()) {
            System.out.println("No hay celdas vacías.");
            return;
        }

        Random rand = new Random();
        int[] pos = emptyCells.get(rand.nextInt(emptyCells.size()));
        int r = pos[0], c = pos[1];
        board[r][c] = solution[r][c];
        isHint[r][c] = true;
        hintsUsed++;
        System.out.println(GREEN + "Pista dada en fila " + (r + 1) + ", columna " + (c + 1) + RESET);
    }

    private static void generateSudoku(String difficulty) {
        clearBoard();
        Random rand = new Random();
        int blanks = switch (difficulty.toLowerCase()) {
            case "medio" -> 45;
            case "dificil" -> 55;
            default -> 35;
        };

        // Rellenar diagonal 3x3
        for (int k = 0; k < SIZE; k += 3) {
            boolean[] used = new boolean[10];
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++) {
                    int num;
                    do {
                        num = rand.nextInt(9) + 1;
                    } while (used[num]);
                    used[num] = true;
                    board[k + r][k + c] = num;
                    isOriginal[k + r][k + c] = true;
                }
        }

        // Resolver para obtener solución completa
        solve(board);
        copyBoard(board, solution);

        // Borrar celdas según dificultad
        int count = 0;
        while (count < blanks) {
            int r = rand.nextInt(SIZE);
            int c = rand.nextInt(SIZE);
            if (board[r][c] != 0) {
                board[r][c] = 0;
                isOriginal[r][c] = false;
                count++;
            }
        }
        hintsUsed = 0;
    }

    private static boolean solve(int[][] b) {
        int[] pos = findEmpty(b);
        if (pos == null) return true;
        int row = pos[0], col = pos[1];
        for (int num = 1; num <= 9; num++) {
            if (isValid(b, row, col, num)) {
                b[row][col] = num;
                if (solve(b)) return true;
                b[row][col] = 0;
            }
        }
        return false;
    }

    private static int[] findEmpty(int[][] b) {
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                if (b[r][c] == 0) return new int[]{r, c};
        return null;
    }

    private static boolean isValid(int[][] b, int row, int col, int num) {
        // Revisar fila y columna
        for (int i = 0; i < SIZE; i++)
            if ((b[row][i] == num && i != col) || (b[i][col] == num && i != row))
                return false;
        // Revisar caja 3x3
        int boxRow = (row / 3) * 3, boxCol = (col / 3) * 3;
        for (int r = boxRow; r < boxRow + 3; r++)
            for (int c = boxCol; c < boxCol + 3; c++)
                if ((r != row || c != col) && b[r][c] == num)
                    return false;
        return true;
    }

    private static void copyBoard(int[][] src, int[][] dest) {
        for (int i = 0; i < SIZE; i++)
            dest[i] = Arrays.copyOf(src[i], SIZE);
    }

    private static void clearBoard() {
        for (int r = 0; r < SIZE; r++) {
            Arrays.fill(board[r], 0);
            Arrays.fill(isOriginal[r], false);
            Arrays.fill(isHint[r], false);
        }
        hintsUsed = 0;
    }
}