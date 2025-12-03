// Demostración Día 1-3: Nodo + Árbol con insertar y listar
#include <iostream>
#include "arbol_fs.h"

int main() {
    ArbolFS fs;

    std::cout << "Creando carpeta 'docs'...\n";
    fs.mkdir("docs");

    std::cout << "Creando archivo 'readme.txt'...\n";
    fs.touch("readme.txt", "Proyecto 123 - Sistema de Archivos");

    std::cout << "Contenido en la ruta actual (/):\n";
    for (const auto& nombre : fs.ls()) {
        std::cout << " - " << nombre << "\n";
    }

    return 0;
}