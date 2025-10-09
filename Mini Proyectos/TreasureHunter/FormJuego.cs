using System;
using System.Drawing;
using System.Windows.Forms;

namespace TreasureHunter
{
    public enum TipoCelda { Vacio, Tesoro, Trampa, Salida }

    public partial class FormJuego : Form
    {
        const int CELL = 25;
        const int SIZE = 20;
        Button[,] grid;
        int playerX = 0, playerY = 0;
        Random rnd = new Random();

        int vidas;
        int energia;
        int puntuacion = 0;
        int nivelActual = 1;
        int movimientosSinChoque = 0;

        private Form _formInicio;

        public FormJuego(Form formInicio)
        {
            InitializeComponent();
            _formInicio = formInicio;

            vidas = 3;
            energia = 4;

            this.KeyPreview = true;
            this.KeyDown += FormJuego_KeyDown;

            CargarNivel(nivelActual);
        }

        private void CargarNivel(int nivel)
        {
            int numTesoros = 0;
            int numTrampas = 0;

            switch (nivel)
            {
                case 1:
                    numTesoros = 25;
                    numTrampas = 10;
                    break;
                case 2:
                    numTesoros = 35;
                    numTrampas = 15;
                    break;
                case 3:
                    numTesoros = 45;
                    numTrampas = 20;
                    break;
            }

            this.Controls.Clear();

            grid = new Button[SIZE, SIZE];
            this.ClientSize = new Size(SIZE * CELL + 200, SIZE * CELL);
            this.Text = $"🏴‍☠️ Treasure Hunter - Nivel {nivel}";

            CrearTablero(numTesoros, numTrampas);

            // Posición inicial
            playerX = 0;
            playerY = 0;
            grid[playerX, playerY].BackColor = Color.Blue;
            grid[playerX, playerY].Text = "👤";

            CrearControlesUI();
            MostrarEstado();
        }

        void CrearTablero(int numTesoros, int numTrampas)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    grid[i, j] = new Button
                    {
                        Size = new Size(CELL, CELL),
                        Location = new Point(j * CELL, i * CELL),
                        BackColor = Color.LightGray,
                        Tag = TipoCelda.Vacio
                    };
                    this.Controls.Add(grid[i, j]);
                }
            }

            // Colocar al menos un tesoro alcanzable desde el inicio
            grid[0, 1].Tag = TipoCelda.Tesoro;
            grid[0, 1].Text = "💰";

            // Colocar el resto de tesoros y trampas
            ColocarElementos(numTesoros - 1, TipoCelda.Tesoro, 2);
            ColocarElementos(numTrampas, TipoCelda.Trampa, 0);

            // Colocar salida
            int sx, sy;
            do
            {
                sx = rnd.Next(SIZE);
                sy = rnd.Next(SIZE);
            } while ((sx == 0 && sy == 0) || (TipoCelda)grid[sx, sy].Tag != TipoCelda.Vacio || (sx + sy < SIZE / 2));

            grid[sx, sy].Tag = TipoCelda.Salida;
            grid[sx, sy].Text = "🏁";
            grid[sx, sy].BackColor = Color.Gold;
        }

        private void ColocarElementos(int cantidad, TipoCelda tipo, int distanciaMinima)
        {
            int colocados = 0;
            int intentos = 0;

            while (colocados < cantidad && intentos < cantidad * 50)
            {
                int x = rnd.Next(SIZE);
                int y = rnd.Next(SIZE);

                if ((TipoCelda)grid[x, y].Tag != TipoCelda.Vacio || (x == 0 && y == 0))
                {
                    intentos++;
                    continue;
                }

                if (tipo == TipoCelda.Tesoro && x + y < distanciaMinima)
                {
                    intentos++;
                    continue;
                }

                bool vecinosOcupados = false;
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && ny >= 0 && nx < SIZE && ny < SIZE)
                        {
                            if ((TipoCelda)grid[nx, ny].Tag != TipoCelda.Vacio)
                                vecinosOcupados = true;
                        }
                    }
                }

                if (vecinosOcupados)
                {
                    intentos++;
                    continue;
                }

                // Colocar elemento
                grid[x, y].Tag = tipo;
                grid[x, y].Text = tipo == TipoCelda.Tesoro ? "💰" : "💀";
                colocados++;
            }
        }


        private void CrearControlesUI()
        {
            Panel controlPanel = new Panel()
            {
                Location = new Point(SIZE * CELL + 10, 50),
                Size = new Size(180, 200)
            };

            Button btnUp = new Button() { Text = "↑", Location = new Point(70, 0), Size = new Size(40, 40) };
            Button btnDown = new Button() { Text = "↓", Location = new Point(70, 80), Size = new Size(40, 40) };
            Button btnLeft = new Button() { Text = "←", Location = new Point(30, 40), Size = new Size(40, 40) };
            Button btnRight = new Button() { Text = "→", Location = new Point(110, 40), Size = new Size(40, 40) };
            Button btnSalir = new Button() { Text = "Menú", Location = new Point(50, 150), Size = new Size(80, 30) };

            btnUp.Click += (s, e) => Mover(-1, 0);
            btnDown.Click += (s, e) => Mover(1, 0);
            btnLeft.Click += (s, e) => Mover(0, -1);
            btnRight.Click += (s, e) => Mover(0, 1);
            btnSalir.Click += (s, e) =>
            {
                this.Hide();
                _formInicio.Show();
            };

            controlPanel.Controls.AddRange(new Control[] { btnUp, btnDown, btnLeft, btnRight, btnSalir });
            this.Controls.Add(controlPanel);
        }

        private void FormJuego_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.W:
                case Keys.Up: Mover(-1, 0); break;
                case Keys.S:
                case Keys.Down: Mover(1, 0); break;
                case Keys.A:
                case Keys.Left: Mover(0, -1); break;
                case Keys.D:
                case Keys.Right: Mover(0, 1); break;
            }
        }

        void Mover(int dx, int dy)
        {
            if (vidas <= 0 || energia <= 0) return;

            int nx = playerX + dx;
            int ny = playerY + dy;

            // Fuera del tablero
            if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE)
            {
                energia--;
                movimientosSinChoque = 0;
                MostrarEstado();
                return;
            }

            // Limpiar celda anterior
            grid[playerX, playerY].Text = "";
            if ((TipoCelda)grid[playerX, playerY].Tag == TipoCelda.Vacio)
                grid[playerX, playerY].BackColor = Color.LightGray;

            playerX = nx;
            playerY = ny;
            energia--;

            movimientosSinChoque++;
            if (movimientosSinChoque >= 3)
            {
                energia++;
                movimientosSinChoque = 0;
            }

            TipoCelda celdaDestino = (TipoCelda)(grid[playerX, playerY].Tag ?? TipoCelda.Vacio);

            if (celdaDestino == TipoCelda.Tesoro)
            {
                puntuacion += 10 * nivelActual;
                energia += 3;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                MessageBox.Show("💰 ¡Tesoro Recolectado!");
            }
            else if (celdaDestino == TipoCelda.Trampa)
            {
                vidas--;
                energia -= 2;
                puntuacion -= 5 * nivelActual;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                MessageBox.Show("💀 ¡Caíste en una trampa!");
                movimientosSinChoque = 0;
            }
            else if (celdaDestino == TipoCelda.Salida)
            {
                if (CheckFinNivel())
                {
                    MessageBox.Show($"🎉 ¡Saliste del laberinto! Nivel {nivelActual} completado.");
                    puntuacion += 50;
                    nivelActual++;

                    if (nivelActual > 3)
                    {
                        MessageBox.Show("🏆 ¡Has completado todos los niveles!");
                        GameOver();
                        return;
                    }

                    CargarNivel(nivelActual);
                    return;
                }
                else
                {
                    MessageBox.Show("🚫 Aún no puedes salir, faltan tesoros por recolectar.");
                }
            }

            grid[playerX, playerY].Text = "👤";
            grid[playerX, playerY].BackColor = Color.Blue;
            MostrarEstado();

            if (vidas <= 0 || energia <= 0)
            {
                GameOver();
            }
        }

        private bool CheckFinNivel()
        {
            foreach (var btn in grid)
                if ((TipoCelda)(btn.Tag ?? TipoCelda.Vacio) == TipoCelda.Tesoro)
                    return false;
            return true;
        }

        void MostrarEstado()
        {
            this.Text = $"🏴‍☠️ Treasure Hunter | Nivel: {nivelActual} | Vidas: {Math.Max(0, vidas)} | Energía: {Math.Max(0, energia)} | Puntos: {puntuacion}";
        }

        void GameOver()
        {
            MessageBox.Show($"Fin del juego 🕹️\nPuntuación final: {puntuacion}");
            this.Hide();
            _formInicio.Show();
            this.Close();
        }
    }
}