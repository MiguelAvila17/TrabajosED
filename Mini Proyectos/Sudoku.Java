import java.util.*;
import java.io.*;

public class Sudoku {
    private static final int SIZE = 9;
    private static int[][] board = new int[SIZE][SIZE];
    private static int[][] solution = new int[SIZE][SIZE];
    private static boolean[][] isOriginal = new boolean[SIZE][SIZE];
    private static boolean[][] isHint = new boolean[SIZE][SIZE];
    private static boolean[][] isError = new boolean[SIZE][SIZE];

    private static int hintsUsed = 0;
    private static int vidas = 5;

    private static Scanner sc = new Scanner(System.in);

    private static final String RESET = "\u001B[0m";
    private static final String WHITE = "\u001B[37m";
    private static final String GREEN = "\u001B[32m";
    private static final String YELLOW = "\u001B[33m";
    private static final String RED = "\u001B[31m";

    private static final String[] niveles = {"Muy Fácil", "Fácil", "Medio", "Difícil", "Muy Difícil"};

    public static void main(String[] args) {
        System.out.println("=== Bienvenido al Sudoku Adventure ===");

        for (int nivel = 0; nivel < niveles.length; nivel++) {
            System.out.println("\nNivel: " + niveles[nivel]);
            for (int tableroNum = 1; tableroNum <= 5; tableroNum++) {
                System.out.println("\nTablero " + tableroNum + " de 5");
                jugarTablero(nivel);
            }
            System.out.println("¡Nivel " + niveles[nivel] + " completado!");
        }
        System.out.println("¡Felicidades! Has completado los 25 tableros del Sudoku Adventure.");
    }

    private static void jugarTablero(int dificultad) {
        int min, max;
        switch (dificultad) {
            case 0 -> { min = 36; max = 44; } // Muy fácil
            case 1 -> { min = 32; max = 35; } // Fácil
            case 2 -> { min = 28; max = 31; } // Medio
            case 3 -> { min = 24; max = 27; } // Difícil
            case 4 -> { min = 17; max = 23; } // Muy difícil
            default -> { min = 32; max = 35; }
        }

        generarTablero(min, max);
        hintsUsed = 0;
        vidas = 5;

        while (true) {
            validarTablero();
            printBoard();
            System.out.println("Vidas restantes: " + vidas);
            System.out.println("Opciones: 1-Insertar número  2-Pedir pista  3-Rendirse  4-Guardar partida  5-Cargar partida");
            int opcion = sc.nextInt();
            sc.nextLine();

            switch (opcion) {
                case 1 -> insertarNumero();
                case 2 -> darPista();
                case 3 -> {
                    System.out.println("Rendirse. Se reiniciará este tablero.");
                    generarTablero(min, max);
                    hintsUsed = 0;
                    vidas = 5;
                }
                case 4 -> guardarPartida("partida_guardada.txt");
                case 5 -> cargarPartida("partida_guardada.txt");
                default -> System.out.println("Opción inválida.");
            }

            if (hayErrores()) {
                vidas--;
                System.out.println(RED + "¡Número conflictivo! Pierdes 1 vida." + RESET);
                if (vidas <= 0) {
                    System.out.println(RED + "Se agotaron las vidas. Se reinicia el tablero." + RESET);
                    generarTablero(min, max);
                    hintsUsed = 0;
                    vidas = 5;
                }
            }

            if (isSolved()) {
                System.out.println(GREEN + "¡Tablero completado correctamente!" + RESET);
                break;
            }
        }
    }

    // === GUARDAR PARTIDA ===
    private static void guardarPartida(String archivo) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(archivo))) {
            pw.println(vidas + " " + hintsUsed);

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) pw.print(board[i][j] + " ");
                pw.println();
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) pw.print(solution[i][j] + " ");
                pw.println();
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) pw.print((isOriginal[i][j] ? 1 : 0) + " ");
                pw.println();
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) pw.print((isHint[i][j] ? 1 : 0) + " ");
                pw.println();
            }

            System.out.println("Partida guardada en " + archivo);
        } catch (Exception e) {
            System.out.println("Error al guardar la partida: " + e.getMessage());
        }
    }

    // === CARGAR PARTIDA ===
    private static void cargarPartida(String archivo) {
        try (Scanner file = new Scanner(new File(archivo))) {
            vidas = file.nextInt();
            hintsUsed = file.nextInt();

            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    board[i][j] = file.nextInt();

            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    solution[i][j] = file.nextInt();

            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    isOriginal[i][j] = (file.nextInt() == 1);

            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    isHint[i][j] = (file.nextInt() == 1);

            System.out.println("Partida cargada correctamente.");
        } catch (Exception e) {
            System.out.println("Error al cargar la partida: " + e.getMessage());
        }
    }

    // === Generar Tablero ===
    private static void generarTablero(int minVisible, int maxVisible) {
        // 1. Generamos la solución completa
        for (int i = 0; i < SIZE; i++) Arrays.fill(solution[i], 0);
        fillBoard(solution);

        // 2. Limpiamos el tablero
        for (int i = 0; i < SIZE; i++)
            Arrays.fill(board[i], 0);

        // 3. Limpiamos la información de casillas originales
        for (int i = 0; i < SIZE; i++)
            Arrays.fill(isOriginal[i], false);

        Random rand = new Random();
        int visibles = minVisible + rand.nextInt(maxVisible - minVisible + 1);
        int count = 0;

        while (count < visibles) {
            int row = rand.nextInt(SIZE);
            int col = rand.nextInt(SIZE);
            if (!isOriginal[row][col]) {
                board[row][col] = solution[row][col];
                isOriginal[row][col] = true;
                count++;
            }
        }

        for (int i = 0; i < SIZE; i++) {
            Arrays.fill(isHint[i], false);
            Arrays.fill(isError[i], false);
        }
    }

    private static boolean fillBoard(int[][] grid) {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    List<Integer> nums = new ArrayList<>();
                    for (int n = 1; n <= SIZE; n++) nums.add(n);
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
            if (grid[row][i] == num) return false;
            if (grid[i][col] == num) return false;
        }
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = startRow; i < startRow + 3; i++)
            for (int j = startCol; j < startCol + 3; j++)
                if (grid[i][j] == num) return false;
        return true;
    }

    private static void printBoard() {
        System.out.println("\n╔═══════╦═══════╦═══════╗");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0) System.out.print("║ ");
                if (board[i][j] == 0) System.out.print(". ");
                else if (isError[i][j]) System.out.print(RED + board[i][j] + RESET + " ");
                else if (isOriginal[i][j]) System.out.print(WHITE + board[i][j] + RESET + " ");
                else if (isHint[i][j]) System.out.print(YELLOW + board[i][j] + RESET + " ");
                else System.out.print(GREEN + board[i][j] + RESET + " ");
            }
            System.out.println("║");
            if (i == 2 || i == 5) System.out.println("╠═══════╬═══════╬═══════╣");
        }
        System.out.println("╚═══════╩═══════╩═══════╝");
        System.out.println("Pistas usadas: " + hintsUsed + "/3");
    }

    private static void insertarNumero() {
        System.out.println("Fila (1-9):");
        int row = sc.nextInt() - 1;
        System.out.println("Columna (1-9):");
        int col = sc.nextInt() - 1;
        System.out.println("Número (1-9):");
        int num = sc.nextInt();

        if (isOriginal[row][col]) System.out.println("No puedes cambiar un número original.");
        else {
            board[row][col] = num;
            isHint[row][col] = false;
        }
    }

    private static void darPista() {
        if (hintsUsed >= 3) {
            System.out.println("Ya usaste las 3 pistas.");
            return;
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == 0) {
                    board[i][j] = solution[i][j];
                    isHint[i][j] = true;
                    hintsUsed++;
                    return;
                }
    }

    private static void validarTablero() {
        for (int i = 0; i < SIZE; i++)
            Arrays.fill(isError[i], false);

        for (int i = 0; i < SIZE; i++) {
            Map<Integer, List<Integer>> fila = new HashMap<>();
            Map<Integer, List<Integer>> col = new HashMap<>();
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 0) fila.computeIfAbsent(board[i][j], k -> new ArrayList<>()).add(j);
                if (board[j][i] != 0) col.computeIfAbsent(board[j][i], k -> new ArrayList<>()).add(j);
            }
            for (List<Integer> l : fila.values()) if (l.size() > 1) for (int c : l) isError[i][c] = true;
            for (List<Integer> l : col.values()) if (l.size() > 1) for (int r : l) isError[r][i] = true;
        }

        for (int boxRow = 0; boxRow < 3; boxRow++)
            for (int boxCol = 0; boxCol < 3; boxCol++) {
                Map<Integer, List<int[]>> nums = new HashMap<>();
                for (int i = boxRow * 3; i < boxRow * 3 + 3; i++)
                    for (int j = boxCol * 3; j < boxCol * 3 + 3; j++)
                        if (board[i][j] != 0)
                            nums.computeIfAbsent(board[i][j], k -> new ArrayList<>()).add(new int[]{i,j});
                for (List<int[]> l : nums.values())
                    if (l.size() > 1)
                        for (int[] pos : l)
                            isError[pos[0]][pos[1]] = true;
            }
    }

    private static boolean hayErrores() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (isError[i][j]) return true;
        return false;
    }

    private static boolean isSolved() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] != solution[i][j]) return false;
        return true;
    }
}