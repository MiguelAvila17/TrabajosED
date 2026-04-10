import javax.swing.*;
import java.awt.*;

public class SistemaEscolar {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Login::new);
    }

    // ===================== LOGIN =====================
    static class Login extends JFrame {
        JTextField txtUser;
        JPasswordField txtPass;

        public Login() {
            setTitle("Login");
            setSize(300, 180);
            setLocationRelativeTo(null);
            setDefaultCloseOperation(EXIT_ON_CLOSE);
            setLayout(new GridLayout(3,2,5,5));

            add(new JLabel("Usuario:"));
            txtUser = new JTextField();
            add(txtUser);

            add(new JLabel("Contraseña:"));
            txtPass = new JPasswordField();
            add(txtPass);

            JButton btnLogin = new JButton("Ingresar");
            add(new JLabel());
            add(btnLogin);

            btnLogin.addActionListener(e -> validar());

            setVisible(true);
        }

        private void validar() {
            if (txtUser.getText().equals("admin") &&
                new String(txtPass.getPassword()).equals("1234")) {

                new Menu();
                dispose();
            } else {
                JOptionPane.showMessageDialog(this, "Error de login");
            }
        }
    }

    // ===================== MENÚ =====================
    static class Menu extends JFrame {

        public Menu() {
            setTitle("Menú Principal");
            setSize(400, 300);
            setLocationRelativeTo(null);
            setLayout(new GridLayout(5,1,10,10));

            add(boton("Alumnos", FormAlumnos::new));
            add(boton("Maestros", FormMaestros::new));
            add(boton("Materias", FormSimple::new));
            add(boton("Grupos", FormSimple::new));
            add(boton("Inscripciones", FormSimple::new));

            setVisible(true);
        }

        private JButton boton(String texto, Runnable accion) {
            JButton b = new JButton(texto);
            b.addActionListener(e -> accion.run());
            return b;
        }
    }

    // ===================== MODELOS =====================
    static class Persona {
        private String nombre;

        public Persona(String nombre) {
            this.nombre = nombre;
        }

        public String getNombre() {
            return nombre;
        }
    }

    static class Alumno extends Persona {
        private String matricula;

        public Alumno(String nombre, String matricula) {
            super(nombre);
            this.matricula = matricula;
        }

        public String getMatricula() {
            return matricula;
        }

        public String toString() {
            return getNombre() + " - " + matricula;
        }
    }

    static class Maestro extends Persona {
        private String especialidad;

        public Maestro(String nombre, String especialidad) {
            super(nombre);
            this.especialidad = especialidad;
        }

        public String getEspecialidad() {
            return especialidad;
        }

        public String toString() {
            return getNombre() + " - " + especialidad;
        }
    }

    // ===================== FORM ALUMNOS =====================
    static class FormAlumnos extends JFrame {

        DefaultListModel<Alumno> modelo = new DefaultListModel<>();
        JList<Alumno> lista = new JList<>(modelo);

        JTextField txtNombre, txtMatricula;

        public FormAlumnos() {
            setTitle("ABC Alumnos");
            setSize(450,400);
            setLocationRelativeTo(null);
            setLayout(new FlowLayout());

            txtNombre = new JTextField(15);
            txtMatricula = new JTextField(10);

            JButton btnAgregar = new JButton("Agregar");
            JButton btnEliminar = new JButton("Eliminar");
            JButton btnActualizar = new JButton("Actualizar");

            add(new JLabel("Nombre:"));
            add(txtNombre);
            add(new JLabel("Matrícula:"));
            add(txtMatricula);

            add(btnAgregar);
            add(btnActualizar);
            add(btnEliminar);

            add(new JScrollPane(lista));

            btnAgregar.addActionListener(e -> agregar());
            btnEliminar.addActionListener(e -> eliminar());
            btnActualizar.addActionListener(e -> actualizar());

            lista.addListSelectionListener(e -> seleccionar());

            setVisible(true);
        }

        void agregar() {
            if (txtNombre.getText().isEmpty() || txtMatricula.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "Campos vacíos");
                return;
            }
            modelo.addElement(new Alumno(txtNombre.getText(), txtMatricula.getText()));
            limpiar();
        }

        void eliminar() {
            int i = lista.getSelectedIndex();
            if (i == -1) {
                JOptionPane.showMessageDialog(this, "Selecciona un alumno");
                return;
            }
            modelo.remove(i);
            limpiar();
        }

        void actualizar() {
            int i = lista.getSelectedIndex();
            if (i == -1) {
                JOptionPane.showMessageDialog(this, "Selecciona un alumno");
                return;
            }
            modelo.set(i, new Alumno(txtNombre.getText(), txtMatricula.getText()));
            limpiar();
        }

        void seleccionar() {
            Alumno a = lista.getSelectedValue();
            if (a != null) {
                txtNombre.setText(a.getNombre());
                txtMatricula.setText(a.getMatricula());
            }
        }

        void limpiar() {
            txtNombre.setText("");
            txtMatricula.setText("");
            lista.clearSelection();
        }
    }

    // ===================== FORM MAESTROS =====================
    static class FormMaestros extends JFrame {

        DefaultListModel<Maestro> modelo = new DefaultListModel<>();
        JList<Maestro> lista = new JList<>(modelo);

        JTextField txtNombre, txtEsp;

        public FormMaestros() {
            setTitle("ABC Maestros");
            setSize(450,400);
            setLocationRelativeTo(null);
            setLayout(new FlowLayout());

            txtNombre = new JTextField(15);
            txtEsp = new JTextField(10);

            JButton btnAgregar = new JButton("Agregar");
            JButton btnEliminar = new JButton("Eliminar");
            JButton btnActualizar = new JButton("Actualizar");

            add(new JLabel("Nombre:"));
            add(txtNombre);
            add(new JLabel("Especialidad:"));
            add(txtEsp);

            add(btnAgregar);
            add(btnActualizar);
            add(btnEliminar);

            add(new JScrollPane(lista));

            btnAgregar.addActionListener(e -> agregar());
            btnEliminar.addActionListener(e -> eliminar());
            btnActualizar.addActionListener(e -> actualizar());

            lista.addListSelectionListener(e -> seleccionar());

            setVisible(true);
        }

        void agregar() {
            if (txtNombre.getText().isEmpty() || txtEsp.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "Campos vacíos");
                return;
            }
            modelo.addElement(new Maestro(txtNombre.getText(), txtEsp.getText()));
            limpiar();
        }

        void eliminar() {
            int i = lista.getSelectedIndex();
            if (i == -1) {
                JOptionPane.showMessageDialog(this, "Selecciona un maestro");
                return;
            }
            modelo.remove(i);
            limpiar();
        }

        void actualizar() {
            int i = lista.getSelectedIndex();
            if (i == -1) {
                JOptionPane.showMessageDialog(this, "Selecciona un maestro");
                return;
            }
            modelo.set(i, new Maestro(txtNombre.getText(), txtEsp.getText()));
            limpiar();
        }

        void seleccionar() {
            Maestro m = lista.getSelectedValue();
            if (m != null) {
                txtNombre.setText(m.getNombre());
                txtEsp.setText(m.getEspecialidad());
            }
        }

        void limpiar() {
            txtNombre.setText("");
            txtEsp.setText("");
            lista.clearSelection();
        }
    }

    // ===================== FORM SIMPLE (Materias, Grupos, Inscripciones) =====================
    static class FormSimple extends JFrame {

        DefaultListModel<String> modelo = new DefaultListModel<>();
        JList<String> lista = new JList<>(modelo);

        JTextField txt;

        public FormSimple() {
            setTitle("Formulario");
            setSize(400,400);
            setLocationRelativeTo(null);
            setLayout(new FlowLayout());

            txt = new JTextField(15);

            JButton btnAgregar = new JButton("Agregar");
            JButton btnEliminar = new JButton("Eliminar");
            JButton btnActualizar = new JButton("Actualizar");

            add(new JLabel("Dato:"));
            add(txt);

            add(btnAgregar);
            add(btnActualizar);
            add(btnEliminar);

            add(new JScrollPane(lista));

            btnAgregar.addActionListener(e -> {
                if (!txt.getText().isEmpty()) {
                    modelo.addElement(txt.getText());
                    txt.setText("");
                }
            });

            btnEliminar.addActionListener(e -> {
                int i = lista.getSelectedIndex();
                if (i != -1) modelo.remove(i);
            });

            btnActualizar.addActionListener(e -> {
                int i = lista.getSelectedIndex();
                if (i != -1) modelo.set(i, txt.getText());
            });

            lista.addListSelectionListener(e -> {
                String val = lista.getSelectedValue();
                if (val != null) txt.setText(val);
            });

            setVisible(true);
        }
    }
}