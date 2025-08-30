class Persona {
    constructor(nombre, edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
    mostrarDatos() {
        console.log(`Nombre: ${this.nombre}, Edad: ${this.edad}`);
    }
}
// Uso
const p1 = new Persona("Miguel Angel", 19);
p1.mostrarDatos();
