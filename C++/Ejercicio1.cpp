#include <iostream>
#include <string>
using namespace std;
// Definición de clase Persona
class Persona {
private:
    string nombre;
    int edad;
public:
    Persona(string n, int e) {
        nombre = n;
        edad = e;
    }
    void mostrarDatos() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
    }
};
// Uso
int main() {
    Persona p1("Miguel Angel", 19);
    p1.mostrarDatos();
    return 0;
}
