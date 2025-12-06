#include "arbol_fs.h"

ArbolFS::ArbolFS() : raiz_(std::make_shared<Nodo>(0, "/", TipoNodo::Carpeta)), actual_(raiz_), siguienteId_(1) {}

bool ArbolFS::mkdir(const std::string& nombre) {
    auto carpeta = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Carpeta);
    trie_.insert(nombre); index_[nombre].push_back(carpeta);
    return actual_->agregarHijo(carpeta);
}
bool ArbolFS::touch(const std::string& nombre, const std::string& contenido) {
    auto archivo = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Archivo, contenido);
    trie_.insert(nombre); index_[nombre].push_back(archivo);
    return actual_->agregarHijo(archivo);
}
std::vector<std::string> ArbolFS::ls() const { std::vector<std::string> r; for (auto& h: actual_->hijos()) r.push_back(h->nombre()); return r; }
std::vector<std::string> ArbolFS::searchPrefix(const std::string& prefijo) const { return trie_.suggest(prefijo); }
std::vector<std::shared_ptr<Nodo>> ArbolFS::searchExact(const std::string& nombre) const {
    auto it = index_.find(nombre); if (it==index_.end()) return {}; return it->second;
}