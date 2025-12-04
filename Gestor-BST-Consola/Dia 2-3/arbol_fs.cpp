#include "arbol_fs.h"

ArbolFS::ArbolFS() : raiz_(std::make_shared<Nodo>(0, "/", TipoNodo::Carpeta)), actual_(raiz_), siguienteId_(1) {}

bool ArbolFS::mkdir(const std::string& nombre) {
    if (actual_->buscarHijoPorNombre(nombre)) return false;
    auto carpeta = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Carpeta);
    return actual_->agregarHijo(carpeta);
}

bool ArbolFS::touch(const std::string& nombre, const std::string& contenido) {
    if (actual_->buscarHijoPorNombre(nombre)) return false;
    auto archivo = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Archivo, contenido);
    return actual_->agregarHijo(archivo);
}

std::vector<std::string> ArbolFS::ls() const {
    std::vector<std::string> nombres;
    for (const auto& h : actual_->hijos()) nombres.push_back(h->nombre());
    return nombres;
}