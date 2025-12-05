// main.cpp
#include "BST.h"
#include <iostream>
#include <sstream>
#include <limits> // Para std::numeric_limits

using namespace std;

const string PERSISTENCE_FILE = "bst_keys.txt";

void mostrar_ayuda() {
    cout << "\n--- Comandos Disponibles ---" << endl;
    cout << "  insert <num>         : Inserta un numero en el BST." << endl;
    cout << "  search <num>         : Busca un numero y muestra el camino." << endl;
    cout << "  delete <num>         : Elimina un numero del BST." << endl;
    cout << "  inorder              : Muestra el recorrido Inorden (ordenado)." << endl;
    cout << "  preorder             : Muestra el recorrido Preorden." << endl;
    cout << "  postorder            : Muestra el recorrido Postorden." << endl;
    cout << "  height               : Muestra la altura del arbol." << endl;
    cout << "  size                 : Muestra el numero total de nodos." << endl;
    cout << "  export               : Guarda el recorrido inorden a '" << PERSISTENCE_FILE << "'." << endl;
    cout << "  help                 : Muestra esta ayuda." << endl;
    cout << "  exit                 : Sale del programa." << endl;
    cout << "---------------------------\n" << endl;
}

// Función auxiliar para imprimir vectores
void imprimir_vector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void main_cli() {
    BST bst;

    // Persistencia Opcional: Cargar datos al inicio
    int loaded_count = bst.cargar_claves(PERSISTENCE_FILE);

    cout << "===================================================" << endl;
    cout << "Gestor de Numeros con Arbol Binario de Busqueda" << endl;
    cout << "===================================================" << endl;
    if (loaded_count > 0) {
        cout << "Se cargaron " << loaded_count << " claves desde '" << PERSISTENCE_FILE << "'." << endl;
    } else {
        cout << "Arbol vacio o archivo de claves no encontrado. Use 'insert <num>'." << endl;
    }
    cout << "Escriba 'help' para ver los comandos." << endl;

    string linea;
    while (true) {
        cout << "\nBST > ";
        getline(cin, linea);

        stringstream ss(linea);
        string comando;
        ss >> comando;

        if (comando.empty()) continue;

        try {
            if (comando == "insert") {
                int key;
                if (ss >> key) {
                    bst.insertar(key);
                    cout << "Numero " << key << " insertado." << endl;
                } else {
                    cout << "Error: El comando 'insert' requiere un numero. Ejemplo: insert 42" << endl;
                }
            } else if (comando == "search") {
                int key;
                if (ss >> key) {
                    vector<int> ruta;
                    if (bst.buscar(key, ruta)) {
                        cout << "Numero " << key << " encontrado." << endl;
                        cout << "   Ruta: "; imprimir_vector(ruta);
                    } else {
                        cout << "Numero " << key << " no encontrado." << endl;
                        cout << "   Ultima ruta: "; imprimir_vector(ruta);
                    }
                } else {
                    cout << "Error: El comando 'search' requiere un numero. Ejemplo: search 42" << endl;
                }
            } else if (comando == "delete") {
                int key;
                if (ss >> key) {
                    bst.eliminar(key);
                    cout << "Intento de eliminacion de " << key << " completado." << endl;
                } else {
                    cout << "Error: El comando 'delete' requiere un numero. Ejemplo: delete 42" << endl;
                }
            } else if (comando == "inorder") {
                cout << "Inorden (Ordenado): "; imprimir_vector(bst.inorden());
            } else if (comando == "preorder") {
                cout << "Preorden: "; imprimir_vector(bst.preorden());
            } else if (comando == "postorder") {
                cout << "Postorden: "; imprimir_vector(bst.postorden());
            } else if (comando == "height") {
                int h = bst.altura();
                // h=-1 para arbol vacio, lo mostramos como 0
                int display_h = (h >= 0) ? h : 0;
                cout << "Altura del arbol: " << display_h << " (Niveles: " << display_h + 1 << ")" << endl;
            } else if (comando == "size") {
                cout << "Numero total de nodos: " << bst.tamano() << endl;
            } else if (comando == "export") {
                if (bst.exportar_inorden(PERSISTENCE_FILE)) {
                    cout << "Recorrido Inorden guardado con exito en '" << PERSISTENCE_FILE << "'." << endl;
                }
            } else if (comando == "help") {
                mostrar_ayuda();
            } else if (comando == "exit") {
                // Guardar estado actual antes de salir
                if (bst.tamano() > 0) {
                    cout << "Guardando estado actual del Inorden en '" << PERSISTENCE_FILE << "' antes de salir..." << endl;
                    bst.exportar_inorden(PERSISTENCE_FILE);
                } else {
                    // Opcional: Eliminar el archivo si el árbol está vacío
                    remove(PERSISTENCE_FILE.c_str());
                    cout << "Archivo de persistencia eliminado, arbol vacio." << endl;
                }
                cout << "¡Adios!" << endl;
                break;
            } else {
                cout << "Comando desconocido: '" << comando << "'. Escriba 'help' para ver los comandos." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: Ocurrio una excepcion: " << e.what() << endl;
        }
    }
}

int main() {
    main_cli();
    return 0;
}