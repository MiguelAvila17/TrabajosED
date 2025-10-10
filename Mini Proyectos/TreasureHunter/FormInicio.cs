using System;
using System.Drawing;
using System.Windows.Forms;

namespace TreasureHunter
{
    public partial class FormInicio : Form
    {
        public FormInicio()
        {
            InitializeComponent();

            this.Text = "🏴‍☠️ Treasure Hunter - Menú Principal";
            this.Width = 400;
            this.Height = 300;
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;

            // --- Título ---
            Label lblTitulo = new Label();
            lblTitulo.Text = "🏴‍☠️ TREASURE HUNTER 🪙";
            lblTitulo.Font = new Font("Arial", 16, FontStyle.Bold);
            lblTitulo.AutoSize = true;
            lblTitulo.Location = new Point(60, 20);
            this.Controls.Add(lblTitulo);

            // --- Botón JUGAR ---
            Button btnJugar = new Button();
            btnJugar.Text = "▶️ Jugar";
            btnJugar.Font = new Font("Arial", 12);
            btnJugar.Size = new Size(120, 50);
            btnJugar.Location = new Point(130, 80);
            btnJugar.BackColor = Color.MediumSeaGreen;
            btnJugar.ForeColor = Color.White;
            btnJugar.Click += BtnJugar_Click;
            this.Controls.Add(btnJugar);

            // --- Botón CARGAR PARTIDA ---
            Button btnCargar = new Button();
            btnCargar.Text = "📂 Cargar partida";
            btnCargar.Font = new Font("Arial", 12);
            btnCargar.Size = new Size(150, 50);
            btnCargar.Location = new Point(120, 140);
            btnCargar.BackColor = Color.Orange;
            btnCargar.ForeColor = Color.White;
            btnCargar.Click += (s, e) =>
            {
                // Abrir diálogo para seleccionar archivo guardado
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "Archivo de partida (*.thp)|*.thp";
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    // Crear FormJuego y cargar la partida
                    FormJuego frm = new FormJuego(this);
                    frm.Show();
                    frm.CargarPartida(ofd.FileName);
                    this.Hide();
                }
            };
            this.Controls.Add(btnCargar);

            // --- Botón INSTRUCCIONES ---
            Button btnInstrucciones = new Button();
            btnInstrucciones.Text = "Instrucciones";
            btnInstrucciones.Font = new Font("Arial", 11);
            btnInstrucciones.Size = new Size(150, 40);
            btnInstrucciones.Location = new Point(120, 140);
            btnInstrucciones.BackColor = Color.SteelBlue;
            btnInstrucciones.ForeColor = Color.White;
            btnInstrucciones.Click += (s, e) =>
            {
                MessageBox.Show(
                    "🧭 REGLAS DEL JUEGO 🧭\n\n" +
                    "1. Empiezas con 3 vidas y 4 puntos de energía.\n" +
                    "2. Recolecta todos los tesoros para poder usar la salida 🏁.\n" +
                    "3. Evita las trampas o perderás vidas y energía.\n" +
                    "4. Cada 3 movimientos sin chocar con paredes ganas 1 energía.\n" +
                    "5. Llega a la salida cuando hayas tomado todos los tesoros para pasar al siguiente nivel.\n" +
                    "6. Son 3 niveles: fácil, medio y difícil.\n\n" +
                    "Usa W, A, S, D o las flechas para moverte.",
                    "Instrucciones",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information
                );
            };
            this.Controls.Add(btnInstrucciones);

            // --- Botón SALIR ---
            Button btnSalir = new Button();
            btnSalir.Text = "❌ Salir";
            btnSalir.Font = new Font("Arial", 12);
            btnSalir.Size = new Size(120, 50);
            btnSalir.Location = new Point(130, 190);
            btnSalir.BackColor = Color.IndianRed;
            btnSalir.ForeColor = Color.White;
            btnSalir.Click += (s, e) => Application.Exit();
            this.Controls.Add(btnSalir);
        }

        // --- Acción para iniciar el juego ---
        private void BtnJugar_Click(object sender, EventArgs e)
        {
            FormJuego frm = new FormJuego(this);
            frm.Show();
            this.Hide();
        }
    }
}