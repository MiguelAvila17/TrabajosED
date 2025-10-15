using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace TreasureHunter
{
    // Tipos de celdas posibles en el tablero
    public enum TipoCelda { Vacio, Tesoro, Trampa, Salida, Muro, Llave }

    public partial class FormJuego : Form
    {
        const int CELL = 25;  // Tamaño de cada celda
        const int SIZE = 20;  // Tamaño del tablero (20x20)
        Button[,] grid;       // Matriz de botones que representa el tablero
        int playerX = 0, playerY = 0;  // Posición actual del jugador
        Random rnd = new Random();     // Generador de números aleatorios

        int vidas;
        int energia;
        int puntuacion = 0;
        int nivelActual = 1;
        int movimientosSinChoque = 0;

        int tesorosRecolectados = 0;
        int trampasEncontradas = 0;
        bool tieneLlave = false;   // Indica si el jugador ya recogió la llave

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

        // Carga un nuevo nivel según el número indicado
        private void CargarNivel(int nivel)
        {
            int numTesoros = 0;
            int numTrampas = 0;
            int numMuros = 0;

            // Ajustamos la cantidad de elementos por nivel
            switch (nivel)
            {
                case 1: numTesoros = 25; numTrampas = 10; numMuros = 60; break;
                case 2: numTesoros = 35; numTrampas = 15; numMuros = 90; break;
                case 3: numTesoros = 45; numTrampas = 20; numMuros = 120; break;
            }

            // Limpiamos controles existentes y preparamos tablero
            this.Controls.Clear();
            grid = new Button[SIZE, SIZE];
            this.ClientSize = new Size(SIZE * CELL + 300, SIZE * CELL);
            this.Text = $"🏴‍☠ Treasure Hunter - Nivel {nivel}";

            // Crear el tablero con tesoros, trampas, muros y salida
            CrearTablero(numTesoros, numTrampas, numMuros);

            // Posición inicial del jugador
            playerX = 0;
            playerY = 0;
            grid[playerX, playerY].BackColor = Color.Blue;
            grid[playerX, playerY].Text = "👤";

            CrearControlesUI();
            MostrarEstado();
        }

        // Crea el tablero con tesoros, trampas, muros, llave y salida
        void CrearTablero(int numTesoros, int numTrampas, int numMuros)
        {
            // Crear botones de la grilla base
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
            grid[0, 1].Text = "";

            // Colocamos los demás elementos
            ColocarElementos(numTesoros - 1, TipoCelda.Tesoro, 2); // Resto de tesoros
            ColocarElementos(numTrampas, TipoCelda.Trampa, 0);     // Trampas
            ColocarElementos(numMuros, TipoCelda.Muro, 0);         // Muros

            // Colocamos la llave en una posición aleatoria
            int lx, ly;
            do
            {
                lx = rnd.Next(SIZE);
                ly = rnd.Next(SIZE);
            } while ((lx == 0 && ly == 0) || (TipoCelda)grid[lx, ly].Tag != TipoCelda.Vacio);

            grid[lx, ly].Tag = TipoCelda.Llave;
            grid[lx, ly].Text = "🔑"; // Oculta la llave al inicio

            // Colocamos la salida en posición aleatoria (oculta)
            int sx, sy;
            do
            {
                sx = rnd.Next(SIZE);
                sy = rnd.Next(SIZE);
            } while ((sx == 0 && sy == 0) || (TipoCelda)grid[sx, sy].Tag != TipoCelda.Vacio || (sx + sy < SIZE / 2));

            grid[sx, sy].Tag = TipoCelda.Salida;
            grid[sx, sy].Text = "🏁"; // salida también oculta al inicio
            grid[sx, sy].BackColor = Color.LightGray;
        }

        // Coloca tesoros, trampas o muros en posiciones válidas
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

                // Evita colocar elementos juntos
                bool vecinosOcupados = false;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++)
                        if (x + dx >= 0 && y + dy >= 0 && x + dx < SIZE && y + dy < SIZE)
                            if ((TipoCelda)grid[x + dx, y + dy].Tag != TipoCelda.Vacio)
                                vecinosOcupados = true;

                if (vecinosOcupados) { intentos++; continue; }

                // Colocamos el elemento
                grid[x, y].Tag = tipo;

                switch (tipo)
                {
                    case TipoCelda.Tesoro:
                    case TipoCelda.Trampa:
                    case TipoCelda.Llave:
                        grid[x, y].Text = ""; // ocultos
                        break;
                    case TipoCelda.Muro:
                        grid[x, y].Text = "⬛"; // ícono visible del muro
                        grid[x, y].BackColor = Color.DarkSlateGray;
                        break;
                }
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

        // Movimientos mediante teclado
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

        // Movimiento del jugador en el tablero
        void Mover(int dx, int dy)
        {
            if (vidas <= 0) return;

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

            // Si la celda destino es un muro, no se puede pasar
            if ((TipoCelda)grid[nx, ny].Tag == TipoCelda.Muro)
            {
                MessageBox.Show("🚧 ¡No puedes pasar, hay un muro!");
                energia--; // quita 1 energía al chocar
                movimientosSinChoque = 0;
                MostrarEstado();
                return;
            }

            // Limpiamos la celda anterior del jugador
            grid[playerX, playerY].Text = "";
            if ((TipoCelda)grid[playerX, playerY].Tag == TipoCelda.Vacio)
                grid[playerX, playerY].BackColor = Color.LightGray;

            // Actualizamos coordenadas
            playerX = nx;
            playerY = ny;

            puntuacion--;
            movimientosSinChoque++;

            // Cada 3 movimientos sin chocar con pared, se aumenta 1 punto de energía
            if (movimientosSinChoque >= 3)
            {
                energia++;
                movimientosSinChoque = 0;
            }

            // Lógica de la celda destino
            TipoCelda celdaDestino = (TipoCelda)(grid[playerX, playerY].Tag ?? TipoCelda.Vacio);

            // Revelar el contenido de la celda al entrar
            if (celdaDestino == TipoCelda.Tesoro) grid[playerX, playerY].Text = "💰";
            else if (celdaDestino == TipoCelda.Trampa) grid[playerX, playerY].Text = "💀";
            else if (celdaDestino == TipoCelda.Salida) grid[playerX, playerY].Text = "🏁";
            else if (celdaDestino == TipoCelda.Llave) grid[playerX, playerY].Text = "🔑";

            // Lógica de tesoro
            if (celdaDestino == TipoCelda.Tesoro)
            {
                puntuacion += 10 * nivelActual;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                grid[playerX, playerY].Text = "";
                tesorosRecolectados++;
                MessageBox.Show("💰 ¡Tesoro Recolectado!");
            }
            // Lógica de trampa
            else if (celdaDestino == TipoCelda.Trampa)
            {
                vidas--;
                puntuacion -= 5 * nivelActual;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                grid[playerX, playerY].Text = "";
                trampasEncontradas++;
                MessageBox.Show("💀 ¡Caíste en una trampa!");
                movimientosSinChoque = 0;
            }
            // Lógica de llave
            else if (celdaDestino == TipoCelda.Llave)
            {
                tieneLlave = true;
                puntuacion += 20 * nivelActual;
                grid[playerX, playerY].Tag = TipoCelda.Vacio;
                grid[playerX, playerY].Text = "🔑";
                MessageBox.Show("🔑 ¡Has encontrado la llave! Ahora puedes salir del nivel.");
            }
            // Lógica de salida
            else if (celdaDestino == TipoCelda.Salida)
            {
                // Verificar si el jugador tiene la llave
                if (!tieneLlave)
                {
                    MessageBox.Show("🚫 La puerta está cerrada. Necesitas la llave 🔑 para salir.");
                    return; // no puede salir aún
                }

                // Con la llave ya puede salir, sin importar los tesoros
                MessageBox.Show($"¡Has usado la llave y escapado del laberinto! Nivel {nivelActual} completado.");
                puntuacion += 50;  // recompensa por salir
                nivelActual++;
                tieneLlave = false; // reseteamos para el siguiente nivel
                if (nivelActual > 3) { GameOver(); return; }
                CargarNivel(nivelActual);
            }

            // Actualizamos posición del jugador en pantalla
            grid[playerX, playerY].Text = "👤";
            grid[playerX, playerY].BackColor = Color.Blue;
            MostrarEstado();
            ActualizarInventario();

            if (vidas <= 0) GameOver();
        }

        // Verifica si aún quedan tesoros por recolectar
        private bool CheckFinNivel()
        {
            foreach (var btn in grid)
                if ((TipoCelda)(btn.Tag ?? TipoCelda.Vacio) == TipoCelda.Tesoro)
                    return false;
            return true;
        }

        // Actualiza título con estadísticas actuales
        void MostrarEstado()
        {
            this.Text = $"🏴‍☠ Treasure Hunter | Nivel: {nivelActual} | Vidas: {Math.Max(0, vidas)} | Energía: {Math.Max(0, energia)} | Puntos: {puntuacion}";
        }

        // Actualiza la información mostrada en el panel de inventario
        void ActualizarInventario()
        {
            txtInventario.Text = "INVENTARIO DEL JUGADOR\r\n";
            txtInventario.Text += "=======================\r\n";
            txtInventario.Text += $"Nivel: {nivelActual}\r\n";
            txtInventario.Text += $"Vidas: {vidas}\r\n";
            txtInventario.Text += $"Energía: {energia}\r\n";
            txtInventario.Text += $"Puntuación: {puntuacion}\r\n";
            txtInventario.Text += $"Tiene llave: {(tieneLlave ? "✅ Sí" : "❌ No")}\r\n";
            txtInventario.Text += "---------------------------\r\n";
            txtInventario.Text += $"Tesoros recolectados: {tesorosRecolectados}\r\n";
            txtInventario.Text += $"Trampas encontradas: {trampasEncontradas}\r\n";
            txtInventario.Text += "=======================\r\n";
        }

        // Muestra mensaje de fin de juego
        void GameOver()
        {
            MessageBox.Show($"Fin del juego 🕹\nPuntuación final: {puntuacion}");
            this.Hide();
            _formInicio.Show();
            this.Close();
        }

        // Guardar partida en archivo
        void GuardarPartida()
        {
            string path = archivoGuardado;
            if (string.IsNullOrEmpty(path))
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "Archivo de partida (.thp)|.thp";
                if (sfd.ShowDialog() != DialogResult.OK) return;
                path = sfd.FileName;
                archivoGuardado = path;
            }

            using (StreamWriter sw = new StreamWriter(path))
            {
                sw.WriteLine(nivelActual);
                sw.WriteLine(playerX);
                sw.WriteLine(playerY);
                sw.WriteLine(vidas);
                sw.WriteLine(energia);
                sw.WriteLine(puntuacion);
                sw.WriteLine(tesorosRecolectados);
                sw.WriteLine(trampasEncontradas);
                sw.WriteLine(tieneLlave ? 1 : 0);

                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        sw.WriteLine((int)(grid[i, j].Tag ?? TipoCelda.Vacio));
            }

            MessageBox.Show("💾 Partida guardada correctamente.");
        }

        // Carga la partida desde archivo
        public void CargarPartida(string archivo)
        {
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
                tieneLlave = sr.ReadLine() == "1";

                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        grid[i, j].Tag = (TipoCelda)int.Parse(sr.ReadLine());
            }

            MostrarEstado();
            ActualizarInventario(); // Actualizamos inventario al cargar partida
        }
    }
}