#include "arbol_fs.h"

ArbolFS::ArbolFS() : raiz_(std::make_shared<Nodo>(0, "/", TipoNodo::Carpeta)), actual_(raiz_), siguienteId_(1) {}

std::shared_ptr<Nodo> ArbolFS::raiz() const { return raiz_; }
std::shared_ptr<Nodo> ArbolFS::actual() const { return actual_; }

bool ArbolFS::mkdir(const std::string& nombre) {
    if (actual_->tipo() != TipoNodo::Carpeta) return false;
    if (actual_->buscarHijoPorNombre(nombre)) return false;
    auto carpeta = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Carpeta);
    carpeta->setPadre(actual_);
    return actual_->agregarHijo(carpeta);
}

bool ArbolFS::touch(const std::string& nombre, const std::string& contenido) {
    if (actual_->tipo() != TipoNodo::Carpeta) return false;
    if (actual_->buscarHijoPorNombre(nombre)) return false;
    auto archivo = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Archivo, contenido);
    archivo->setPadre(actual_);
    return actual_->agregarHijo(archivo);
}

std::vector<std::string> ArbolFS::ls() const {
    std::vector<std::string> nombres;
    for (const auto& h : actual_->hijos()) {
        nombres.push_back(h->nombre());
    }
    return nombres;
}