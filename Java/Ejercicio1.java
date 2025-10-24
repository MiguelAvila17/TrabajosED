class Persona {   
    String nombre;
    int edad;
    Persona(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
    void mostrarDatos() {
        System.out.println("Nombre: " + nombre + ", Edad: " + edad);
    }
}
public class Ejercicio1 {
    public static void main(String[] args) {
        Persona p1 = new Persona("Miguel Angel", 19);
        p1.mostrarDatos();
    }
}