// BST.cpp
#include "BST.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// --- Constructor y Destructor ---

BST::BST() : raiz(nullptr) {}

BST::~BST() {
    destruir_arbol(raiz);
}

void BST::destruir_arbol(Nodo* nodo) {
    if (nodo != nullptr) {
        destruir_arbol(nodo->izquierda);
        destruir_arbol(nodo->derecha);
        delete nodo;
    }
}

// --- Operaciones Principales ---

void BST::insertar(int clave) {
    raiz = _insertar_recursivo(raiz, clave);
}

// O(log n) promedio
Nodo* BST::_insertar_recursivo(Nodo* nodo, int clave) {
    if (nodo == nullptr) {
        return new Nodo(clave);
    }

    if (clave < nodo->clave) {
        nodo->izquierda = _insertar_recursivo(nodo->izquierda, clave);
    } else if (clave > nodo->clave) {
        nodo->derecha = _insertar_recursivo(nodo->derecha, clave);
    }
    // Clave igual: se ignora (no se permiten duplicados)

    return nodo;
}

// O(log n) promedio
bool BST::buscar(int clave, std::vector<int>& ruta) {
    Nodo* actual = raiz;
    ruta.clear();

    while (actual != nullptr) {
        ruta.push_back(actual->clave);
        if (clave == actual->clave) {
            return true; // Encontrado
        } else if (clave < actual->clave) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }
    return false; // No encontrado
}

// O(log n) promedio
void BST::eliminar(int clave) {
    raiz = _eliminar_recursivo(raiz, clave);
}

Nodo* BST::_encontrar_minimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierda != nullptr) {
        actual = actual->izquierda;
    }
    return actual;
}

Nodo* BST::_eliminar_recursivo(Nodo* nodo, int clave) {
    if (nodo == nullptr) {
        std::cout << "Error: La clave " << clave << " no existe en el arbol." << std::endl;
        return nullptr;
    }

    // 1. Recorrer para encontrar el nodo a eliminar
    if (clave < nodo->clave) {
        nodo->izquierda = _eliminar_recursivo(nodo->izquierda, clave);
    } else if (clave > nodo->clave) {
        nodo->derecha = _eliminar_recursivo(nodo->derecha, clave);
    } else {
        // 2. Nodo encontrado, manejar los 3 casos de eliminación:

        // Caso 1: Cero o Un hijo (hoja o solo hijo derecho)
        if (nodo->izquierda == nullptr) {
            Nodo* temp = nodo->derecha;
            delete nodo;
            return temp;
        }
        // Caso 1: Un hijo (solo hijo izquierdo)
        else if (nodo->derecha == nullptr) {
            Nodo* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Caso 2: Dos hijos
        // Encontrar el sucesor inorden (el menor en el subárbol derecho)
        Nodo* temp = _encontrar_minimo(nodo->derecha);

        // Copiar la clave del sucesor inorden a este nodo
        nodo->clave = temp->clave;

        // Eliminar el sucesor inorden de su posición original
        nodo->derecha = _eliminar_recursivo(nodo->derecha, temp->clave);
    }

    return nodo;
}

// --- Recorridos ---

std::vector<int> BST::inorden() {
    std::vector<int> resultado;
    _inorden_recursivo(raiz, resultado);
    return resultado;
}

void BST::_inorden_recursivo(Nodo* nodo, std::vector<int>& resultado) {
    if (nodo != nullptr) {
        _inorden_recursivo(nodo->izquierda, resultado);
        resultado.push_back(nodo->clave);
        _inorden_recursivo(nodo->derecha, resultado);
    }
}

std::vector<int> BST::preorden() {
    std::vector<int> resultado;
    _preorden_recursivo(raiz, resultado);
    return resultado;
}

void BST::_preorden_recursivo(Nodo* nodo, std::vector<int>& resultado) {
    if (nodo != nullptr) {
        resultado.push_back(nodo->clave);
        _preorden_recursivo(nodo->izquierda, resultado);
        _preorden_recursivo(nodo->derecha, resultado);
    }
}

std::vector<int> BST::postorden() {
    std::vector<int> resultado;
    _postorden_recursivo(raiz, resultado);
    return resultado;
}

void BST::_postorden_recursivo(Nodo* nodo, std::vector<int>& resultado) {
    if (nodo != nullptr) {
        _postorden_recursivo(nodo->izquierda, resultado);
        _postorden_recursivo(nodo->derecha, resultado);
        resultado.push_back(nodo->clave);
    }
}

// --- Métricas ---

int BST::altura() {
    return _altura_recursiva(raiz);
}

// O(n)
int BST::_altura_recursiva(Nodo* nodo) {
    if (nodo == nullptr) {
        return -1; // Altura de un árbol vacío
    }
    int alt_izq = _altura_recursiva(nodo->izquierda);
    int alt_der = _altura_recursiva(nodo->derecha);
    return 1 + std::max(alt_izq, alt_der);
}

int BST::tamano() {
    return _tamano_recursivo(raiz);
}

// O(n)
int BST::_tamano_recursivo(Nodo* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return 1 + _tamano_recursivo(nodo->izquierda) + _tamano_recursivo(nodo->derecha);
}

// --- Persistencia ---

// O(n)
bool BST::exportar_inorden(const std::string& nombre_archivo) {
    std::vector<int> data = inorden();
    std::ofstream archivo(nombre_archivo);

    if (archivo.is_open()) {
        for (size_t i = 0; i < data.size(); ++i) {
            archivo << data[i];
            if (i < data.size() - 1) {
                archivo << " ";
            }
        }
        archivo.close();
        return true;
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << " para escritura." << std::endl;
        return false;
    }
}

// O(k log n) donde k es el número de claves
int BST::cargar_claves(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    int count = 0;

    if (archivo.is_open()) {
        int clave;
        // Leer cada número del archivo
        while (archivo >> clave) {
            this->insertar(clave);
            count++;
        }
        archivo.close();
        return count;
    } else {
        std::cout << "Advertencia: Archivo de persistencia '" << nombre_archivo << "' no encontrado." << std::endl;
        return 0;
    }
}