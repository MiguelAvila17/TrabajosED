#include "json_io.h"
#include <sstream>

static void escribir(const std::shared_ptr<Nodo>& n, std::ostringstream& os) {
    os << "{";
    os << "\"id\":" << n->id() << ",";
    os << "\"nombre\":\"" << n->nombre() << "\",";
    os << "\"tipo\":\"" << (n->tipo()==TipoNodo::Carpeta?"carpeta":"archivo") << "\",";
    os << "\"contenido\":\"" << n->contenido() << "\",";
    os << "\"hijos\":[";
    const auto& hijos = n->hijos();
    for (size_t i=0;i<hijos.size();++i) { escribir(hijos[i], os); if (i+1<hijos.size()) os << ","; }
    os << "]";
    os << "}";
}

std::string serializarJson(const std::shared_ptr<Nodo>& n) {
    std::ostringstream os; escribir(n, os); return os.str();
}

std::shared_ptr<Nodo> cargarJson(const std::string& contenido) {
    size_t i = contenido.find("\"id\":"); if (i==std::string::npos) return nullptr; i += 5; size_t j = contenido.find(',', i); auto id = std::stoull(contenido.substr(i, j-i));
    i = contenido.find("\"nombre\":\"", j); if (i==std::string::npos) return nullptr; i += 11; j = contenido.find('"', i); auto nombre = contenido.substr(i, j-i);
    i = contenido.find("\"tipo\":\"", j); i += 9; j = contenido.find('"', i); auto tipoStr = contenido.substr(i, j-i); auto tipo = tipoStr=="carpeta"?TipoNodo::Carpeta:TipoNodo::Archivo;
    i = contenido.find("\"contenido\":\"", j); i += 14; j = contenido.find('"', i); auto cont = contenido.substr(i, j-i);
    auto nodo = std::make_shared<Nodo>(id, nombre, tipo, cont);
    i = contenido.find("\"hijos\":[", j); if (i==std::string::npos) return nodo; i += 9;
    size_t k = i; int depth=0; size_t start=std::string::npos;
    while (k < contenido.size()) {
        if (contenido[k]=='{') { if (depth==0) start=k; depth++; }
        else if (contenido[k]=='}') { depth--; if (depth==0 && start!=std::string::npos) { auto childStr = contenido.substr(start, k-start+1); nodo->agregarHijo(cargarJson(childStr)); start=std::string::npos; } }
        else if (contenido[k]==']' && depth==0) break;
        k++;
    }
    return nodo;
}