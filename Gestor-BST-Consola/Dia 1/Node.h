#include <string>
#include <vector>
#include <memory> // Para usar std::shared_ptr

// Declaración anticipada de la clase Node para evitar dependencias circulares
class Node;

// Definición del tipo para la lista de hijos, usando punteros compartidos
// para una mejor gestión de memoria automática (RAII)
using NodePtr = std::shared_ptr<Node>;
using ChildrenList = std::vector<NodePtr>;

class Node {
public:
    // Propiedades del nodo
    std::string id;
    std::string nombre;
    std::string tipo;      // "carpeta" o "archivo"
    std::string contenido; // Contenido (vacío/nulo si es carpeta)

    // Estructura de árbol: lista de hijos
    ChildrenList children; 

    // Constructor para inicializar el nodo
    Node(const std::string& id_val, const std::string& name, const std::string& type, const std::string& content = "");

    // Método de ayuda para imprimir el nodo (útil para la depuración)
    std::string toString() const;
};

// Implementación del constructor (generalmente en el .cpp, pero para simplicidad lo ponemos aquí)
Node::Node(const std::string& id_val, const std::string& name, const std::string& type, const std::string& content)
    : id(id_val), nombre(name), tipo(type), contenido(content) {
    // Si es archivo, la lista de hijos es implícitamente vacía.
}

// Implementación del toString
std::string Node::toString() const {
    return "[" + tipo + "] " + nombre + " (ID: " + id + ")";
}