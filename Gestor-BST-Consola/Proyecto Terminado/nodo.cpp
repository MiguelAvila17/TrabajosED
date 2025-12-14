#include "nodo.h"

Nodo::Nodo(std::uint64_t id, std::string nombre, TipoNodo tipo, std::string contenido)
    : id_(id), nombre_(std::move(nombre)), tipo_(tipo), contenido_(std::move(contenido)) {}
std::uint64_t Nodo::id() const { return id_; }
const std::string& Nodo::nombre() const { return nombre_; }
TipoNodo Nodo::tipo() const { return tipo_; }
const std::string& Nodo::contenido() const { return contenido_; }
void Nodo::setContenido(const std::string& contenido) { contenido_ = contenido; }
const std::vector<std::shared_ptr<Nodo>>& Nodo::hijos() const { return hijos_; }
bool Nodo::agregarHijo(const std::shared_ptr<Nodo>& hijo) {
    for (const auto& h : hijos_) if (h->nombre() == hijo->nombre()) return false;
    hijos_.push_back(hijo); return true;
}
bool Nodo::eliminarHijoPorNombre(const std::string& nombre) {
    for (auto it = hijos_.begin(); it != hijos_.end(); ++it) if ((*it)->nombre() == nombre) { hijos_.erase(it); return true; }
    return false;
}
std::shared_ptr<Nodo> Nodo::buscarHijoPorNombre(const std::string& nombre) const {
    for (const auto& h : hijos_) if (h->nombre() == nombre) return h; return nullptr;
}