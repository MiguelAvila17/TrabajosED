// BST.h
#ifndef BST_H
#define BST_H

#include "Nodo.h"
#include <vector>
#include <string>

class BST {
private:
    Nodo *raiz;

    // Métodos privados auxiliares para recursión

    // Inserción (O(log n) promedio, O(n) peor caso)
    Nodo* _insertar_recursivo(Nodo* nodo, int clave);

    // Eliminación (O(log n) promedio, O(n) peor caso)
    Nodo* _eliminar_recursivo(Nodo* nodo, int clave);
    Nodo* _encontrar_minimo(Nodo* nodo); // Auxiliar para el caso de dos hijos

    // Recorridos (O(n) en todos los casos)
    void _inorden_recursivo(Nodo* nodo, std::vector<int>& resultado);
    void _preorden_recursivo(Nodo* nodo, std::vector<int>& resultado);
    void _postorden_recursivo(Nodo* nodo, std::vector<int>& resultado);

    // Métricas (O(n) en todos los casos)
    int _altura_recursiva(Nodo* nodo);
    int _tamano_recursivo(Nodo* nodo);

public:
    // Constructor y Destructor
    BST();
    ~BST();
    void destruir_arbol(Nodo* nodo); // Auxiliar para el destructor

    // Operaciones principales
    void insertar(int clave);
    bool buscar(int clave, std::vector<int>& ruta);
    void eliminar(int clave);

    // Recorridos y Métricas
    std::vector<int> inorden();
    std::vector<int> preorden();
    std::vector<int> postorden();
    int altura();
    int tamano();
    bool exportar_inorden(const std::string& nombre_archivo);

    // Persistencia opcional
    int cargar_claves(const std::string& nombre_archivo);
};

#endif // BST_H