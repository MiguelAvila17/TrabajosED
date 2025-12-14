#include "arbol_fs.h"
#include "json_io.h"
#include <fstream>
#include <algorithm>

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
bool ArbolFS::save(const std::string& path) const { std::ofstream f(path); if (!f) return false; f << serializarJson(raiz_); return true; }
bool ArbolFS::load(const std::string& path) { std::ifstream f(path); if (!f) return false; std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); auto nueva = cargarJson(s); if (!nueva) return false; raiz_ = nueva; actual_ = raiz_; siguienteId_ = 1; return true; }
static std::size_t countNodes(const std::shared_ptr<Nodo>& n){ if(!n) return 0; std::size_t c=1; for(const auto& h: n->hijos()) c += countNodes(h); return c; }
std::size_t ArbolFS::size() const { return countNodes(raiz_); }
static std::size_t heightRec(const std::shared_ptr<Nodo>& n){ if(!n) return 0; std::size_t h=1; std::size_t mh=0; for(const auto& c: n->hijos()) mh = std::max(mh, heightRec(c)); return h + mh; }
std::size_t ArbolFS::height() const { return heightRec(raiz_); }

static std::shared_ptr<Nodo> findParent(const std::shared_ptr<Nodo>& cur, const std::shared_ptr<Nodo>& target){
    if (!cur) return nullptr;
    for (const auto& h : cur->hijos()) {
        if (h == target) return cur;
        auto p = findParent(h, target);
        if (p) return p;
    }
    return nullptr;
}

bool ArbolFS::cd(const std::string& nombre) {
    if (nombre.empty()) return false;
    std::shared_ptr<Nodo> cur = (nombre[0] == '/') ? raiz_ : actual_;
    std::size_t start = (nombre[0] == '/') ? 1 : 0;
    std::size_t i = start;
    while (i <= nombre.size()) {
        std::size_t j = nombre.find('/', i);
        std::string seg = (j == std::string::npos) ? nombre.substr(i) : nombre.substr(i, j - i);
        if (!seg.empty()) {
            if (seg == ".") { }
            else if (seg == "..") { auto p = findParent(raiz_, cur); if (!p) return false; cur = p; }
            else { auto next = cur->buscarHijoPorNombre(seg); if (!next || next->tipo() != TipoNodo::Carpeta) return false; cur = next; }
        }
        if (j == std::string::npos) break; else i = j + 1;
    }
    actual_ = cur;
    return true;
}

static bool buildPath(const std::shared_ptr<Nodo>& cur, const std::shared_ptr<Nodo>& target, std::vector<std::string>& path){
    if (!cur) return false;
    path.push_back(cur->nombre());
    if (cur == target) return true;
    for (const auto& h : cur->hijos()) {
        if (buildPath(h, target, path)) return true;
    }
    path.pop_back();
    return false;
}

std::string ArbolFS::pwd() const {
    std::vector<std::string> path;
    buildPath(raiz_, actual_, path);
    std::string s;
    for (size_t i=0;i<path.size();++i) {
        if (i==0) s += path[i]; else s += "/" + path[i];
    }
    return s.empty()?"/":s;
}

static void renderTree(const std::shared_ptr<Nodo>& n, std::vector<std::string>& out, int depth){
    if(!n) return;
    std::string prefix(depth*2, ' ');
    std::string tag = n->tipo()==TipoNodo::Carpeta?"[D] ":"[F] ";
    out.push_back(prefix + tag + n->nombre());
    for(const auto& h: n->hijos()) renderTree(h, out, depth+1);
}

std::vector<std::string> ArbolFS::tree() const { std::vector<std::string> lines; renderTree(actual_, lines, 0); return lines; }
std::vector<std::string> ArbolFS::treeFromRoot() const { std::vector<std::string> lines; renderTree(raiz_, lines, 0); return lines; }