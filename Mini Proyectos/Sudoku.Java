import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class SudokuGUI extends JFrame {

    private final JTextField[][] cells = new JTextField[9][9];
    private final int[][] board = new int[9][9];
    private final JComboBox<String> difficultyBox;
    private final JLabel timerLabel;
    private final JLabel hintsLabel;

    private int[][] solution;
    private int hintsUsed = 0;
    private Timer timer;
    private int elapsedSeconds = 0;

    public SudokuGUI() {
        setTitle("Sudoku Deluxe 🧩");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 700);
        setLocationRelativeTo(null);

        JPanel gridPanel = new JPanel(new GridLayout(9, 9));
        Font font = new Font("SansSerif", Font.BOLD, 20);

        // Crear celdas
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                JTextField tf = new JTextField();
                tf.setHorizontalAlignment(JTextField.CENTER);
                tf.setFont(font);
                int top = (r % 3 == 0) ? 3 : 1;
                int left = (c % 3 == 0) ? 3 : 1;
                int bottom = (r == 8) ? 3 : 1;
                int right = (c == 8) ? 3 : 1;
                tf.setBorder(BorderFactory.createMatteBorder(top, left, bottom, right, Color.BLACK));
                final int row = r, col = c;

                // Detectar cambios para validar errores
                tf.addKeyListener(new KeyAdapter() {
                    @Override
                    public void keyReleased(KeyEvent e) {
                        validateCell(row, col);
                    }
                });

                cells[r][c] = tf;
                gridPanel.add(tf);
            }
        }

        // Botones
        JButton solveButton = new JButton("Resolver Sudoku");
        JButton clearButton = new JButton("Limpiar");
        JButton newButton = new JButton("Nuevo Sudoku");
        JButton hintButton = new JButton("Pista 💡");

        difficultyBox = new JComboBox<>(new String[]{"Fácil", "Medio", "Difícil"});
        timerLabel = new JLabel("⏱ Tiempo: 00:00");
        hintsLabel = new JLabel("💡 Pistas usadas: 0/3");

        Font smallFont = new Font("SansSerif", Font.PLAIN, 14);
        timerLabel.setFont(smallFont);
        hintsLabel.setFont(smallFont);

        // Panel inferior
        JPanel infoPanel = new JPanel(new GridLayout(2, 1));
        JPanel topBar = new JPanel();
        topBar.add(new JLabel("Dificultad:"));
        topBar.add(difficultyBox);
        topBar.add(newButton);
        topBar.add(solveButton);
        topBar.add(hintButton);
        topBar.add(clearButton);

        JPanel statusBar = new JPanel();
        statusBar.add(timerLabel);
        statusBar.add(hintsLabel);

        infoPanel.add(topBar);
        infoPanel.add(statusBar);

        add(gridPanel, BorderLayout.CENTER);
        add(infoPanel, BorderLayout.SOUTH);

        // Acciones de los botones
        newButton.addActionListener(e -> {
            generateSudoku();
            displayBoard();
            resetTimer();
        });

        solveButton.addActionListener(e -> {
            if (readBoard()) {
                if (solve(board)) {
                    displayBoard();
                    stopTimer();
                } else {
                    JOptionPane.showMessageDialog(this, "No tiene solución válida.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        clearButton.addActionListener(e -> {
            clearBoard();
            stopTimer();
            resetTimer();
        });

        hintButton.addActionListener(e -> giveHint());

        // Generar Sudoku inicial
        generateSudoku();
        displayBoard();
        startTimer();

        setVisible(true);
    }

    // === GENERADOR ===
    private void generateSudoku() {
        clearBoard();
        fillDiagonalBoxes();
        solve(board);
        solution = copyBoard(board);

        String diff = (String) difficultyBox.getSelectedItem();
        int blanks = switch (diff) {
            case "Medio" -> 45;
            case "Difícil" -> 55;
            default -> 35;
        };

        Random rand = new Random();
        int count = 0;
        while (count < blanks) {
            int r = rand.nextInt(9);
            int c = rand.nextInt(9);
            if (board[r][c] != 0) {
                board[r][c] = 0;
                count++;
            }
        }

        hintsUsed = 0;
        hintsLabel.setText("💡 Pistas usadas: 0/3");
    }

    private void fillDiagonalBoxes() {
        Random rand = new Random();
        for (int k = 0; k < 9; k += 3) {
            boolean[] used = new boolean[10];
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    int num;
                    do {
                        num = rand.nextInt(9) + 1;
                    } while (used[num]);
                    used[num] = true;
                    board[k + r][k + c] = num;
                }
            }
        }
    }

    // === FUNCIÓN DE PISTA CON LÍMITE ===
    private void giveHint() {
        if (solution == null) {
            JOptionPane.showMessageDialog(this, "Primero genera un Sudoku.", "Sin solución cargada", JOptionPane.WARNING_MESSAGE);
            return;
        }

        if (hintsUsed >= 3) {
            JOptionPane.showMessageDialog(this, "Ya usaste las 3 pistas disponibles.", "Límite alcanzado", JOptionPane.WARNING_MESSAGE);
            return;
        }

        readBoard();
        List<int[]> emptyCells = new ArrayList<>();
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
                if (board[r][c] == 0)
                    emptyCells.add(new int[]{r, c});

        if (emptyCells.isEmpty()) {
            JOptionPane.showMessageDialog(this, "El Sudoku ya está completo.", "Sin celdas vacías", JOptionPane.INFORMATION_MESSAGE);
            return;
        }

        Random rand = new Random();
        int[] pos = emptyCells.get(rand.nextInt(emptyCells.size()));
        int r = pos[0], c = pos[1];
        board[r][c] = solution[r][c];
        cells[r][c].setText(String.valueOf(solution[r][c]));
        cells[r][c].setEditable(false);
        cells[r][c].setForeground(new Color(0, 128, 0)); // verde

        hintsUsed++;
        hintsLabel.setText("💡 Pistas usadas: " + hintsUsed + "/3");
    }

    // === VALIDACIÓN DE CELDAS ===
    private void validateCell(int r, int c) {
        String text = cells[r][c].getText().trim();
        if (text.isEmpty()) {
            cells[r][c].setForeground(Color.BLACK);
            return;
        }
        try {
            int num = Integer.parseInt(text);
            if (num < 1 || num > 9 || !isValid(board, r, c, num, true)) {
                cells[r][c].setForeground(Color.RED);
            } else {
                cells[r][c].setForeground(Color.BLACK);
                board[r][c] = num;
            }
        } catch (NumberFormatException e) {
            cells[r][c].setForeground(Color.RED);
        }
    }

    // === TEMPORIZADOR ===
    private void startTimer() {
        timer = new Timer(1000, e -> {
            elapsedSeconds++;
            int minutes = elapsedSeconds / 60;
            int seconds = elapsedSeconds % 60;
            timerLabel.setText(String.format("⏱ Tiempo: %02d:%02d", minutes, seconds));
        });
        timer.start();
    }

    private void stopTimer() {
        if (timer != null) timer.stop();
    }

    private void resetTimer() {
        stopTimer();
        elapsedSeconds = 0;
        timerLabel.setText("⏱ Tiempo: 00:00");
        startTimer();
    }

    // === MÉTODOS AUXILIARES ===
    private int[][] copyBoard(int[][] src) {
        int[][] copy = new int[9][9];
        for (int i = 0; i < 9; i++)
            copy[i] = Arrays.copyOf(src[i], 9);
        return copy;
    }

    private boolean readBoard() {
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++) {
                String text = cells[r][c].getText().trim();
                board[r][c] = text.isEmpty() ? 0 : Integer.parseInt(text.replaceAll("\\D", "0"));
            }
        return true;
    }

    private void displayBoard() {
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == 0) {
                    cells[r][c].setText("");
                    cells[r][c].setEditable(true);
                    cells[r][c].setForeground(Color.BLACK);
                } else {
                    cells[r][c].setText(String.valueOf(board[r][c]));
                    cells[r][c].setEditable(false);
                    cells[r][c].setForeground(new Color(30, 30, 150));
                }
            }
    }

    private void clearBoard() {
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++) {
                board[r][c] = 0;
                cells[r][c].setText("");
                cells[r][c].setEditable(true);
                cells[r][c].setForeground(Color.BLACK);
            }
    }

    // === SOLUCIONADOR ===
    private boolean solve(int[][] board) {
        int[] pos = findEmpty(board);
        if (pos == null) return true;
        int row = pos[0], col = pos[1];
        for (int num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num, false)) {
                board[row][col] = num;
                if (solve(board)) return true;
                board[row][col] = 0;
            }
        }
        return false;
    }

    private int[] findEmpty(int[][] board) {
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
                if (board[r][c] == 0)
                    return new int[]{r, c};
        return null;
    }

    private boolean isValid(int[][] board, int row, int col, int num, boolean temporaryCheck) {
        int current = board[row][col];
        if (!temporaryCheck) board[row][col] = 0;

        for (int i = 0; i < 9; i++)
            if ((board[row][i] == num) || (board[i][col] == num))
                return false;

        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;
        for (int r = boxRow; r < boxRow + 3; r++)
            for (int c = boxCol; c < boxCol + 3; c++)
                if (board[r][c] == num)
                    return false;

        if (!temporaryCheck) board[row][col] = current;
        return true;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SudokuGUI::new);
    }
}