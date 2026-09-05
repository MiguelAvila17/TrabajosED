import java.util.Scanner;

public class AnalizadorLexico {

    // ==========================================================
    // MATRIZ DE TRANSICIÓN
    // ==========================================================
    /*
       COLUMNAS:
       0 = LETRA
       1 = DIGITO
       2 = PUNTO .
       3 = E/e
       4 = SIGNO +/-
       5 = OTRO

       ESTADOS:
       q0 = Inicio
       q1 = Variable (letras)
       q2 = Variable (letras + números)
       q3 = Número entero
       q4 = Punto decimal
       q5 = Número real
       q6 = E/e
       q7 = Signo del exponente
       q8 = Exponente
       q9 = Error
    */

    static int[][] matriz = {

        //  L   D   .   E   S   O
        {  1,  3,  9,  9,  9,  9 }, // q0
        {  1,  2,  9,  9,  9,  9 }, // q1
        {  9,  2,  9,  9,  9,  9 }, // q2
        {  9,  3,  4,  6,  9,  9 }, // q3
        {  9,  5,  9,  9,  9,  9 }, // q4
        {  9,  5,  9,  6,  9,  9 }, // q5
        {  9,  8,  9,  9,  7,  9 }, // q6
        {  9,  8,  9,  9,  9,  9 }, // q7
        {  9,  8,  9,  9,  9,  9 }, // q8
        {  9,  9,  9,  9,  9,  9 }  // q9
    };

    // ==========================================================
    // PALABRAS RESERVADAS
    // ==========================================================

    static String[] palabrasReservadas = {
        "if",
        "else",
        "while",
        "for",
        "do",
        "switch",
        "case",
        "break",
        "continue",
        "int",
        "float",
        "double",
        "char",
        "string",
        "boolean",
        "return",
        "void",
        "public",
        "private",
        "protected",
        "class",
        "static",
        "new",
        "true",
        "false",
        "null"
    };

    // ==========================================================
    // SIMBOLOS SIMPLES
    // ==========================================================

    static char[] simbolosSimples = {
        '+', '-', '*', '/', '=', '<', '>',
        '(', ')', '{', '}', '[', ']',
        ';', ',', '.', ':'
    };

    // ==========================================================
    // SIMBOLOS COMPUESTOS
    // ==========================================================

    static String[] simbolosCompuestos = {
        "==",
        "!=",
        "<=",
        ">=",
        "++",
        "--",
        "&&",
        "||",
        "+=",
        "-=",
        "*=",
        "/="
    };

    // ==========================================================
    // PROGRAMA PRINCIPAL
    // ==========================================================

    public static void main(String[] args) {

        Scanner teclado = new Scanner(System.in);

        System.out.println("==============================================");
        System.out.println("          ANALIZADOR LEXICO");
        System.out.println("==============================================");
        System.out.println("Ingrese una palabra o token a la vez.");
        System.out.println("Escriba SALIR para terminar.");
        System.out.println();

        while (true) {

            System.out.print("Entrada: ");
            String entrada = teclado.nextLine();

            // Terminar programa
            if (entrada.equalsIgnoreCase("SALIR")) {
                System.out.println();
                System.out.println("Programa terminado.");
                break;
            }

            analizar(entrada);

            System.out.println();
        }

        teclado.close();
    }

    // ==========================================================
    // ANALIZAR ENTRADA
    // ==========================================================

    public static void analizar(String entrada) {

        if (entrada.length() == 0) {

            System.out.println("RESULTADO: ERROR");
            System.out.println("Tipo: ENTRADA VACIA");
            System.out.println("Solucion: escriba una palabra o token.");

            return;
        }

        // ------------------------------------------------------
        // CADENA
        // ------------------------------------------------------

        if (esCadena(entrada)) {

            System.out.println("RESULTADO: VALIDA");
            System.out.println("Tipo: CADENA");

            return;
        }

        // ------------------------------------------------------
        // CADENA MAL FORMADA
        // ------------------------------------------------------

        if (entrada.charAt(0) == '"') {

            System.out.println("RESULTADO: ERROR");
            System.out.println("Tipo: CADENA MAL FORMADA");
            System.out.println(
                "Solucion: la cadena debe comenzar y terminar con \""
            );

            return;
        }

        // ------------------------------------------------------
        // SIMBOLO COMPUESTO
        // ------------------------------------------------------

        if (esSimboloCompuesto(entrada)) {

            System.out.println("RESULTADO: VALIDA");
            System.out.println("Tipo: SIMBOLO COMPUESTO");

            return;
        }

        // ------------------------------------------------------
        // SIMBOLO SIMPLE
        // ------------------------------------------------------

        if (esSimboloSimple(entrada)) {

            System.out.println("RESULTADO: VALIDA");
            System.out.println("Tipo: SIMBOLO SIMPLE");

            return;
        }

        // ------------------------------------------------------
        // PALABRA RESERVADA
        // ------------------------------------------------------

        if (esPalabraReservada(entrada)) {

            System.out.println("RESULTADO: VALIDA");
            System.out.println("Tipo: PALABRA RESERVADA");

            return;
        }

        // ------------------------------------------------------
        // MATRIZ DE TRANSICION
        // ------------------------------------------------------

        int resultado = analizarConMatriz(entrada);

        switch (resultado) {

            case 1:

                System.out.println("RESULTADO: VALIDA");
                System.out.println("Tipo: VARIABLE");

                break;

            case 2:

                System.out.println("RESULTADO: VALIDA");
                System.out.println("Tipo: NUMERO ENTERO");

                break;

            case 3:

                System.out.println("RESULTADO: VALIDA");
                System.out.println("Tipo: NUMERO REAL");

                break;

            case 4:

                System.out.println("RESULTADO: VALIDA");
                System.out.println("Tipo: NUMERO CIENTIFICO");

                break;

            default:

                mostrarError(entrada);

                break;
        }
    }

    // ==========================================================
    // ANALIZAR CON MATRIZ
    // ==========================================================

    public static int analizarConMatriz(String entrada) {

        int estado = 0;

        boolean tienePunto = false;
        boolean tieneExponente = false;

        for (int i = 0; i < entrada.length(); i++) {

            char caracter = entrada.charAt(i);

            int columna = obtenerColumna(caracter);

            // --------------------------------------------------
            // SIGNO
            // --------------------------------------------------

            if (columna == 4) {

                // Un signo solamente puede estar al inicio
                // o después de E/e.

                if (i != 0) {

                    char anterior = entrada.charAt(i - 1);

                    if (anterior != 'E' && anterior != 'e') {

                        return -1;
                    }
                }
            }

            // --------------------------------------------------
            // TRANSICION
            // --------------------------------------------------

            int nuevoEstado = matriz[estado][columna];

            if (nuevoEstado == 9) {

                return -1;
            }

            // --------------------------------------------------
            // PUNTO DECIMAL
            // --------------------------------------------------

            if (caracter == '.') {

                if (tienePunto) {

                    return -1;
                }

                tienePunto = true;
            }

            // --------------------------------------------------
            // EXPONENTE
            // --------------------------------------------------

            if (caracter == 'E' || caracter == 'e') {

                if (tieneExponente) {

                    return -1;
                }

                tieneExponente = true;
            }

            estado = nuevoEstado;
        }

        // ======================================================
        // ESTADOS FINALES
        // ======================================================

        // Variable
        if (estado == 1 || estado == 2) {

            if (variableValida(entrada)) {

                return 1;
            }

            return -1;
        }

        // Número entero
        if (estado == 3) {

            return 2;
        }

        // Número real
        if (estado == 5) {

            return 3;
        }

        // Número científico
        if (estado == 8) {

            return 4;
        }

        return -1;
    }

    // ==========================================================
    // OBTENER COLUMNA
    // ==========================================================

    public static int obtenerColumna(char caracter) {

        if (esLetra(caracter)) {

            return 0;
        }

        if (esDigito(caracter)) {

            return 1;
        }

        if (caracter == '.') {

            return 2;
        }

        if (caracter == 'E' || caracter == 'e') {

            return 3;
        }

        if (caracter == '+' || caracter == '-') {

            return 4;
        }

        return 5;
    }

    // ==========================================================
    // VALIDAR VARIABLE
    // ==========================================================

    public static boolean variableValida(String palabra) {

        if (palabra.length() == 0) {

            return false;
        }

        // El primer caracter debe ser una letra

        if (!esLetra(palabra.charAt(0))) {

            return false;
        }

        boolean aparecioNumero = false;

        for (int i = 1; i < palabra.length(); i++) {

            char caracter = palabra.charAt(i);

            // Si es número
            if (esDigito(caracter)) {

                aparecioNumero = true;
            }

            // Si es letra
            else if (esLetra(caracter)) {

                // Después de aparecer un número
                // ya no se permiten letras.

                if (aparecioNumero) {

                    return false;
                }
            }

            else {

                return false;
            }
        }

        return true;
    }

    // ==========================================================
    // SABER SI ES LETRA
    // ==========================================================

    public static boolean esLetra(char caracter) {

        return (caracter >= 'A' && caracter <= 'Z') ||
               (caracter >= 'a' && caracter <= 'z');
    }

    // ==========================================================
    // SABER SI ES DIGITO
    // ==========================================================

    public static boolean esDigito(char caracter) {

        return caracter >= '0' && caracter <= '9';
    }

    // ==========================================================
    // PALABRA RESERVADA
    // ==========================================================

    public static boolean esPalabraReservada(String palabra) {

        for (int i = 0; i < palabrasReservadas.length; i++) {

            if (palabra.equals(palabrasReservadas[i])) {

                return true;
            }
        }

        return false;
    }

    // ==========================================================
    // SIMBOLO SIMPLE
    // ==========================================================

    public static boolean esSimboloSimple(String palabra) {

        if (palabra.length() != 1) {

            return false;
        }

        char caracter = palabra.charAt(0);

        for (int i = 0; i < simbolosSimples.length; i++) {

            if (caracter == simbolosSimples[i]) {

                return true;
            }
        }

        return false;
    }

    // ==========================================================
    // SIMBOLO COMPUESTO
    // ==========================================================

    public static boolean esSimboloCompuesto(String palabra) {

        for (int i = 0; i < simbolosCompuestos.length; i++) {

            if (palabra.equals(simbolosCompuestos[i])) {

                return true;
            }
        }

        return false;
    }

    // ==========================================================
    // CADENA
    // ==========================================================

    public static boolean esCadena(String palabra) {

        if (palabra.length() < 2) {

            return false;
        }

        // Debe comenzar con comillas

        if (palabra.charAt(0) != '"') {

            return false;
        }

        // Debe terminar con comillas

        if (palabra.charAt(palabra.length() - 1) != '"') {

            return false;
        }

        // No debe contener otra comilla dentro

        for (int i = 1; i < palabra.length() - 1; i++) {

            if (palabra.charAt(i) == '"') {

                return false;
            }
        }

        return true;
    }

    // ==========================================================
    // MOSTRAR ERROR
    // ==========================================================

    public static void mostrarError(String entrada) {

        System.out.println("RESULTADO: ERROR LEXICO");

        // ------------------------------------------------------
        // VARIABLE CON LETRA DESPUES DE NUMERO
        // ------------------------------------------------------

        if (esLetra(entrada.charAt(0))) {

            boolean aparecioNumero = false;

            for (int i = 1; i < entrada.length(); i++) {

                char caracter = entrada.charAt(i);

                if (esDigito(caracter)) {

                    aparecioNumero = true;
                }

                else if (esLetra(caracter) && aparecioNumero) {

                    System.out.println(
                        "Causa: despues de utilizar numeros en una variable "
                        + "no se permiten mas letras."
                    );

                    System.out.println(
                        "Solucion: utilice una variable como abc123."
                    );

                    return;
                }
            }
        }

        // ------------------------------------------------------
        // NUMERO CON LETRAS
        // ------------------------------------------------------

        if (esDigito(entrada.charAt(0))) {

            for (int i = 0; i < entrada.length(); i++) {

                if (esLetra(entrada.charAt(i))) {

                    // Puede ser E/e si forma parte de científico

                    if (entrada.charAt(i) == 'E' ||
                        entrada.charAt(i) == 'e') {

                        continue;
                    }

                    System.out.println(
                        "Causa: el numero contiene letras no permitidas."
                    );

                    System.out.println(
                        "Solucion: utilice solamente numeros o "
                        + "notacion cientifica."
                    );

                    return;
                }
            }
        }

        // ------------------------------------------------------
        // MAS DE UN PUNTO
        // ------------------------------------------------------

        int cantidadPuntos = 0;

        for (int i = 0; i < entrada.length(); i++) {

            if (entrada.charAt(i) == '.') {

                cantidadPuntos++;
            }
        }

        if (cantidadPuntos > 1) {

            System.out.println(
                "Causa: el numero contiene mas de un punto decimal."
            );

            System.out.println(
                "Solucion: utilice solamente un punto decimal. "
                + "Ejemplo: 12.50"
            );

            return;
        }

        // ------------------------------------------------------
        // EXPONENTE INCOMPLETO
        // ------------------------------------------------------

        for (int i = 0; i < entrada.length(); i++) {

            if (entrada.charAt(i) == 'E' ||
                entrada.charAt(i) == 'e') {

                if (i == entrada.length() - 1) {

                    System.out.println(
                        "Causa: falta el valor del exponente."
                    );

                    System.out.println(
                        "Solucion: escriba un numero como 2E10."
                    );

                    return;
                }

                if (i + 1 < entrada.length()) {

                    char siguiente = entrada.charAt(i + 1);

                    if (siguiente == '+' || siguiente == '-') {

                        if (i + 2 >= entrada.length()) {

                            System.out.println(
                                "Causa: falta el numero del exponente."
                            );

                            System.out.println(
                                "Solucion: escriba, por ejemplo, 5E-3."
                            );

                            return;
                        }
                    }
                }
            }
        }

        // ------------------------------------------------------
        // ERROR GENERAL
        // ------------------------------------------------------

        System.out.println(
            "Causa: la entrada no cumple ninguna regla del lenguaje."
        );

        System.out.println(
            "Solucion: revise que el token tenga una estructura valida."
        );
    }
}
```
