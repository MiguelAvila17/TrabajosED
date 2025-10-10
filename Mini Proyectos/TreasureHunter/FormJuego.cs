using System;
using System.Drawing;
using System.IO;
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

        int tesorosRecolectados = 0;
        int trampasEncontradas = 0;

        private Form _formInicio;
        private TextBox txtInventario;
        string archivoGuardado = "";

        // Constructor normal
        public FormJuego(Form formInicio)
        {
            InitializeComponent();
            _formInicio = formInicio;

            vidas = 3;      // Vidas iniciales
            energia = 4;    // Energía inicial

            this.KeyPreview = true;
            this.KeyDown += FormJuego_KeyDown;

            CargarNivel(nivelActual);
        }

        // Constructor para cargar partida
        public FormJuego(Form formInicio, string archivo) : this(formInicio)
        {
            archivoGuardado = archivo;
            CargarPartida(archivoGuardado);
        }

        private void CargarNivel(int nivel)
        {
            int numTesoros = 0;
            int numTrampas = 0;

            switch (nivel)
            {
                case 1: numTesoros = 25; numTrampas = 10; break;
                case 2: numTesoros = 35; numTrampas = 15; break;
                case 3: numTesoros = 45; numTrampas = 20; break;
            }

            // Limpiamos controles existentes y preparamos tablero
            this.Controls.Clear();
            grid = new Button[SIZE, SIZE];
            this.ClientSize = new Size(SIZE * CELL + 300, SIZE * CELL);
            this.Text = $"🏴‍☠️ Treasure Hunter - Nivel {nivel}";

            CrearTablero(numTesoros, numTrampas);

            // Posición inicial del jugador
            playerX = 0;
            playerY = 0;
            grid[playerX, playerY].BackColor = Color.Blue;
            grid[playerX, playerY].Text = "👤";

            CrearControlesUI();
            MostrarEstado();
        }

        // Crea el tablero con tesoros, trampas y salida
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

            // Colocamos un tesoro cerca del inicio
            grid[0, 1].Tag = TipoCelda.Tesoro;
            grid[0, 1].Text = "💰";

            ColocarElementos(numTesoros - 1, TipoCelda.Tesoro, 2); // Resto de tesoros
            ColocarElementos(numTrampas, TipoCelda.Trampa, 0);     // Trampas

            // Colocamos la salida en posición aleatoria
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

        // Coloca tesoros o trampas en posiciones válidas
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

                if (tipo == TipoCelda.Tesoro && x + y < distanciaMinima) { intentos++; continue; }

                bool vecinosOcupados = false;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++)
                        if (x + dx >= 0 && y + dy >= 0 && x + dx < SIZE && y + dy < SIZE)
                            if ((TipoCelda)grid[x + dx, y + dy].Tag != TipoCelda.Vacio)
                                vecinosOcupados = true;

                if (vecinosOcupados) { intentos++; continue; }

                // Colocamos el elemento en la celda seleccionada
                grid[x, y].Tag = tipo;
                grid[x, y].Text = tipo == TipoCelda.Tesoro ? "💰" : "💀";
                colocados++;
            }
        }

        // Crear botones y panel de control
        private void CrearControlesUI()
        {
            Panel controlPanel = new Panel()
            {
                Location = new Point(SIZE * CELL + 10, 10),
                Size = new Size(260, SIZE * CELL)
            };

            // Botones de movimiento
            Button btnUp = new Button() { Text = "↑", Location = new Point(90, 0), Size = new Size(40, 40) };
            Button btnDown = new Button() { Text = "↓", Location = new Point(90, 80), Size = new Size(40, 40) };
            Button btnLeft = new Button() { Text = "←", Location = new Point(50, 40), Size = new Size(40, 40) };
            Button btnRight = new Button() { Text = "→", Location = new Point(130, 40), Size = new Size(40, 40) };

            // Botones de menú y guardar
            Button btnSalir = new Button() { Text = "Menú", Location = new Point(60, 130), Size = new Size(80, 30) };
            Button btnGuardar = new Button() { Text = "💾 Guardar", Location = new Point(160, 130), Size = new Size(80, 30) };

            // Asociamos acciones a los botones
            btnUp.Click += (s, e) => Mover(-1, 0);
            btnDown.Click += (s, e) => Mover(1, 0);
            btnLeft.Click += (s, e) => Mover(0, -1);
            btnRight.Click += (s, e) => Mover(0, 1);
            btnSalir.Click += (s, e) => { this.Hide(); _formInicio.Show(); };
            btnGuardar.Click += (s, e) => GuardarPartida();

            // Caja de texto del inventario
            txtInventario = new TextBox()
            {
                Location = new Point(10, 180),
                Size = new Size(240, 250),
                Multiline = true,
                ReadOnly = true,
                ScrollBars = ScrollBars.Vertical,
                Font = new Font("Segoe UI", 10, FontStyle.Bold)
            };
            ActualizarInventario(); // Inicializamos inventario al cargar nivel

            controlPanel.Controls.AddRange(new Control[] { btnUp, btnDown, btnLeft, btnRight, btnSalir, btnGuardar, txtInventario });
            this.Controls.Add(controlPanel);
        }

        private void FormJuego_KeyDown(object sender, KeyEventArgs e)
        {
            // Movimientos mediante teclado
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

            // Verificamos límites del tablero
            if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE)
            {
                energia--;
                movimientosSinChoque = 0;
                MostrarEstado();
                return;
            }

            // Limpiamos la celda anterior
            grid[playerX, playerY].Text = "";
            if ((TipoCelda)grid[playerX, playerY].Tag == TipoCelda.Vacio)
                grid[playerX, playerY].BackColor = Color.LightGray;

            playerX = nx;
            playerY = ny;
            energia--;

            // Incrementamos energía por movimiento seguro
            movimientosSinChoque++;
            if (movimientosSinChoque >= 3)
            {
                energia++;
                movimientosSinChoque = 0;
            }

            // Lógica de la celda destino
            TipoCelda celdaDestino = (TipoCelda)(grid[playerX, playerY].Tag ?? TipoCelda.Vacio);

            if (celdaDestino == TipoCelda.Tesoro)
            {
                // Recolectamos tesoro
                puntuacion += 10 * nivelActual;
                energia += 3;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                tesorosRecolectados++;
                MessageBox.Show("💰 ¡Tesoro Recolectado!");
            }
            else if (celdaDestino == TipoCelda.Trampa)
            {
                // Caemos en trampa
                vidas--;
                energia -= 2;
                puntuacion -= 5 * nivelActual;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                trampasEncontradas++;
                MessageBox.Show("💀 ¡Caíste en una trampa!");
                movimientosSinChoque = 0;
            }
            else if (celdaDestino == TipoCelda.Salida)
            {
                if (CheckFinNivel())
                {
                    MessageBox.Show($"¡Saliste del laberinto! Nivel {nivelActual} completado.");
                    puntuacion += 50;
                    nivelActual++;
                    if (nivelActual > 3) { GameOver(); return; }
                    CargarNivel(nivelActual);
                    return;
                }
                else MessageBox.Show("🚫 Aún no puedes salir, faltan tesoros por recolectar.");
            }

            // Actualizamos posición del jugador
            grid[playerX, playerY].Text = "👤";
            grid[playerX, playerY].BackColor = Color.Blue;
            MostrarEstado();
            ActualizarInventario(); // Actualizamos inventario tras cada movimiento

            if (vidas <= 0 || energia <= 0) GameOver();
        }

        private bool CheckFinNivel()
        {
            // Verifica si aún quedan tesoros por recolectar
            foreach (var btn in grid)
                if ((TipoCelda)(btn.Tag ?? TipoCelda.Vacio) == TipoCelda.Tesoro)
                    return false;
            return true;
        }

        void MostrarEstado()
        {
            // Actualiza título con estadísticas actuales
            this.Text = $"🏴‍☠️ Treasure Hunter | Nivel: {nivelActual} | Vidas: {Math.Max(0, vidas)} | Energía: {Math.Max(0, energia)} | Puntos: {puntuacion}";
        }

        void ActualizarInventario()
        {
            // Encabezado del inventario
            txtInventario.Text = "INVENTARIO DEL JUGADOR\r\n";
            txtInventario.Text += "=======================\r\n";

            // Estadísticas generales
            txtInventario.Text += $"Nivel: {nivelActual}\r\n";
            txtInventario.Text += $"Vidas: {vidas}\r\n";
            txtInventario.Text += $"Energía: {energia}\r\n";
            txtInventario.Text += $"Puntuación: {puntuacion}\r\n";
            txtInventario.Text += "---------------------------\r\n";

            // Tesoros y trampas
            txtInventario.Text += $"Tesoros recolectados: {tesorosRecolectados}\r\n";
            txtInventario.Text += $"Trampas encontradas: {trampasEncontradas}\r\n";

            txtInventario.Text += "=======================\r\n";
        }

        void GameOver()
        {
            // Muestra mensaje de fin de juego
            MessageBox.Show($"Fin del juego 🕹️\nPuntuación final: {puntuacion}");
            this.Hide();
            _formInicio.Show();
            this.Close();
        }

        void GuardarPartida()
        {
            // Guardar partida en archivo
            string path = archivoGuardado;
            if (string.IsNullOrEmpty(path))
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "Archivo de partida (*.thp)|*.thp";
                if (sfd.ShowDialog() != DialogResult.OK) return;
                path = sfd.FileName;
                archivoGuardado = path;
            }

            using (StreamWriter sw = new StreamWriter(path))
            {
                // Guardamos estadísticas y tablero
                sw.WriteLine(nivelActual);
                sw.WriteLine(playerX);
                sw.WriteLine(playerY);
                sw.WriteLine(vidas);
                sw.WriteLine(energia);
                sw.WriteLine(puntuacion);
                sw.WriteLine(tesorosRecolectados);
                sw.WriteLine(trampasEncontradas);

                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        sw.WriteLine((int)(grid[i, j].Tag ?? TipoCelda.Vacio));
            }

            MessageBox.Show("💾 Partida guardada correctamente.");
        }

        public void CargarPartida(string archivo)
        {
            // Carga la partida desde archivo
            if (!File.Exists(archivo)) return;

            using (StreamReader sr = new StreamReader(archivo))
            {
                nivelActual = int.Parse(sr.ReadLine());
                playerX = int.Parse(sr.ReadLine());
                playerY = int.Parse(sr.ReadLine());
                vidas = int.Parse(sr.ReadLine());
                energia = int.Parse(sr.ReadLine());
                puntuacion = int.Parse(sr.ReadLine());
                tesorosRecolectados = int.Parse(sr.ReadLine());
                trampasEncontradas = int.Parse(sr.ReadLine());

                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        grid[i, j].Tag = (TipoCelda)int.Parse(sr.ReadLine());
            }

            MostrarEstado();
            ActualizarInventario(); // Actualizamos inventario al cargar partida
        }
    }
}