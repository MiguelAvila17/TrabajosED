import javax.swing.*;
import java.awt.*;
import java.io.FileWriter;
import java.io.IOException;

public class SubneteoApp extends JFrame {

    private JTextField txtIP, txtValor;
    private JTextArea areaResultado;
    private JRadioButton rbSubredes, rbHosts;
    private ButtonGroup grupo;
    private JButton btnCalcular, btnGuardar;

    public SubneteoApp() {
        configurarVentana();
        inicializarComponentes();
        setVisible(true);
    }

    private void configurarVentana() {
        setTitle("Sistema de Subneteo");
        setSize(850, 700);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout(15, 15));
    }

    private void inicializarComponentes() {
        // PANEL DE ENTRADA DE DATOS
        JPanel panelTop = new JPanel(new GridLayout(4, 2, 10, 10));
        panelTop.setBorder(BorderFactory.createTitledBorder("Configuración de Red"));

        panelTop.add(new JLabel(" Dirección IP Base (ej: 192.168.1.0):"));
        txtIP = new JTextField("192.168.1.0");
        panelTop.add(txtIP);

        panelTop.add(new JLabel(" Cantidad Requerida:"));
        txtValor = new JTextField();
        panelTop.add(txtValor);

        rbSubredes = new JRadioButton("Subredes", true);
        rbHosts = new JRadioButton("Hosts por subred");
        grupo = new ButtonGroup();
        grupo.add(rbSubredes);
        grupo.add(rbHosts);

        panelTop.add(new JLabel(" Tipo de cálculo:"));
        JPanel pRadio = new JPanel(new FlowLayout(FlowLayout.LEFT));
        pRadio.add(rbSubredes);
        pRadio.add(rbHosts);
        panelTop.add(pRadio);

        add(panelTop, BorderLayout.NORTH);

        // ÁREA DE RESULTADOS
        areaResultado = new JTextArea();
        areaResultado.setFont(new Font("Monospaced", Font.PLAIN, 13));
        areaResultado.setEditable(false);
        areaResultado.setBackground(new Color(245, 245, 245));
        add(new JScrollPane(areaResultado), BorderLayout.CENTER);

        // BOTONES
        JPanel panelBotones = new JPanel();
        btnCalcular = new JButton("Calcular Subredes");
        btnGuardar = new JButton("Guardar Reporte (.txt)");

        btnCalcular.addActionListener(e -> calcular());
        btnGuardar.addActionListener(e -> guardar());

        panelBotones.add(btnCalcular);
        panelBotones.add(btnGuardar);
        add(panelBotones, BorderLayout.SOUTH);
    }

    private void calcular() {
        StringBuilder sb = new StringBuilder();
        try {
            String ipStr = txtIP.getText().trim();
            if (txtValor.getText().isEmpty()) throw new Exception("Debe ingresar una cantidad.");
            int valorReq = Integer.parseInt(txtValor.getText().trim());
            long ipLong = ipToLong(ipStr);

            // 1. Identificar Clase y CIDR base
            int primerOcteto = (int) (ipLong >> 24) & 0xFF;
            int cidrBase;
            if (primerOcteto >= 1 && primerOcteto <= 126) cidrBase = 8;       // Clase A
            else if (primerOcteto >= 128 && primerOcteto <= 191) cidrBase = 16; // Clase B
            else if (primerOcteto >= 192 && primerOcteto <= 223) cidrBase = 24; // Clase C
            else throw new Exception("Dirección IP fuera de rango comercial (Clase D/E o inválida).");

            int bitsHostOriginales = 32 - cidrBase;

            // 2. Calcular bits prestados (n)
            int n = 0; 
            if (rbSubredes.isSelected()) {
                while (Math.pow(2, n) < valorReq) n++;
            } else {
                int h = 0;
                while ((Math.pow(2, h) - 2) < valorReq) h++;
                n = bitsHostOriginales - h;
            }

            int nuevoCIDR = cidrBase + n;
            if (nuevoCIDR > 30) throw new Exception("El requerimiento excede la capacidad de la red (Máscara > /30).");

            // 3. Cálculos Teóricos vs Prácticos
            long subredesTeoricas = (long) Math.pow(2, n);
            long subredesPracticas = (subredesTeoricas > 2) ? subredesTeoricas - 2 : subredesTeoricas;
            
            long hostsTeoricos = (long) Math.pow(2, 32 - nuevoCIDR);
            long hostsPracticos = hostsTeoricos - 2;

            // 4. Construcción del Reporte
            sb.append("====================================================================\n");
            sb.append("                       REPORTE DE SUBNETEO                          \n");
            sb.append("====================================================================\n");
            sb.append(String.format(" IP Base: %-15s | Máscara: /%d (%s)\n\n", 
                      ipStr, nuevoCIDR, cidrToMask(nuevoCIDR)));
            
            sb.append(String.format(" SUBREDES -> Teóricas: %-10d | Prácticas: %d\n", 
                      subredesTeoricas, subredesPracticas));
            sb.append(String.format(" HOSTS    -> Teóricos: %-10d | Prácticos: %d\n", 
                      hostsTeoricos, hostsPracticos));
            sb.append("--------------------------------------------------------------------\n\n");
            
            sb.append(String.format("%-8s %-18s %-35s %-18s\n", 
                      "No.", "ID de Red", "Rango de Hosts Útiles", "Broadcast"));

            // CICLO SIN LÍMITE (Muestra todas las subredes)
            for (int i = 0; i < subredesTeoricas; i++) {
                long networkID = ipLong + (i * hostsTeoricos);
                long firstHost = networkID + 1;
                long lastHost = networkID + hostsTeoricos - 2;
                long broadcast = networkID + hostsTeoricos - 1;

                sb.append(String.format("%-8d %-18s %-35s %-18s\n", 
                    (i + 1), 
                    longToIp(networkID), 
                    longToIp(firstHost) + " - " + longToIp(lastHost), 
                    longToIp(broadcast)));
            }

            areaResultado.setText(sb.toString());
            areaResultado.setCaretPosition(0); 

        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Por favor ingrese solo números en la cantidad.", "Error", JOptionPane.ERROR_MESSAGE);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private long ipToLong(String ip) throws Exception {
        String[] octetos = ip.split("\\.");
        if (octetos.length != 4) throw new Exception("La IP debe tener 4 octetos (ej: 192.168.1.0)");
        long result = 0;
        for (int i = 0; i < 4; i++) {
            long val = Long.parseLong(octetos[i]);
            if (val < 0 || val > 255) throw new Exception("Octeto fuera de rango (0-255).");
            result |= (val << (24 - (8 * i)));
        }
        return result;
    }

    private String longToIp(long ip) {
        return String.format("%d.%d.%d.%d", 
               (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
    }

    private String cidrToMask(int cidr) {
        long mask = (0xFFFFFFFFL << (32 - cidr)) & 0xFFFFFFFFL;
        return longToIp(mask);
    }

    private void guardar() {
        if (areaResultado.getText().isEmpty()) {
            JOptionPane.showMessageDialog(this, "No hay datos para guardar.");
            return;
        }
        try (FileWriter fw = new FileWriter("Reporte_Subneteo_Completo.txt")) {
            fw.write(areaResultado.getText());
            JOptionPane.showMessageDialog(this, "Reporte exportado exitosamente.");
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Error al escribir el archivo.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SubneteoApp());
    }
}