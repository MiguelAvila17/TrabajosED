#include "arbol_fs.h"

ArbolFS::ArbolFS() : raiz_(std::make_shared<Nodo>(0, "/", TipoNodo::Carpeta)), actual_(raiz_), siguienteId_(1) {}

bool ArbolFS::mkdir(const std::string& nombre) {
    auto carpeta = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Carpeta);
    if (!actual_->agregarHijo(carpeta)) return false;
    trie_.insert(nombre); index_[nombre].push_back(carpeta); return true;
}
bool ArbolFS::touch(const std::string& nombre, const std::string& contenido) {
    auto archivo = std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Archivo, contenido);
    if (!actual_->agregarHijo(archivo)) return false;
    trie_.insert(nombre); index_[nombre].push_back(archivo); return true;
}
bool ArbolFS::mv(const std::string& nombre, const std::string& destino) {
    auto nodo = actual_->buscarHijoPorNombre(nombre); if (!nodo) return false;
    auto dest = actual_->buscarHijoPorNombre(destino); if (!dest) return false;
    if (dest->tipo() != TipoNodo::Carpeta) return false;
    if (!actual_->eliminarHijoPorNombre(nombre)) return false;
    return dest->agregarHijo(nodo);
}
bool ArbolFS::rm(const std::string& nombre) {
    auto nodo = actual_->buscarHijoPorNombre(nombre); if (!nodo) return false;
    papelera_.push_back(nodo);
    return actual_->eliminarHijoPorNombre(nombre);
}
std::vector<std::string> ArbolFS::ls() const { std::vector<std::string> r; for (auto& h: actual_->hijos()) r.push_back(h->nombre()); return r; }
std::vector<std::string> ArbolFS::searchPrefix(const std::string& prefijo) const { return trie_.suggest(prefijo); }
std::vector<std::shared_ptr<Nodo>> ArbolFS::searchExact(const std::string& nombre) const { auto it=index_.find(nombre); if (it==index_.end()) return {}; return it->second; }
static void pre(const std::shared_ptr<Nodo>& n, std::vector<std::string>& out){ if(!n) return; out.push_back(n->nombre()); for(auto& h:n->hijos()) pre(h,out);} 
void ArbolFS::exportPreorden(std::vector<std::string>& out) const { pre(raiz_, out); }

static std::size_t countNodes(const std::shared_ptr<Nodo>& n){ if(!n) return 0; std::size_t c=1; for(const auto& h: n->hijos()) c += countNodes(h); return c; }
std::size_t ArbolFS::size() const { return countNodes(raiz_); }

static std::size_t heightRec(const std::shared_ptr<Nodo>& n){ if(!n) return 0; std::size_t h=1; std::size_t mh=0; for(const auto& c: n->hijos()) mh = std::max(mh, heightRec(c)); return h + mh; }
std::size_t ArbolFS::height() const { return heightRec(raiz_); }