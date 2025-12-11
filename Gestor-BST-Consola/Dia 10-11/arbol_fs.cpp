#include "arbol_fs.h"
ArbolFS::ArbolFS() : raiz_(std::make_shared<Nodo>(0, "/", TipoNodo::Carpeta)), actual_(raiz_), siguienteId_(1) {}
bool ArbolFS::mkdir(const std::string& nombre){ return actual_->agregarHijo(std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Carpeta)); }
bool ArbolFS::touch(const std::string& nombre, const std::string& contenido){ return actual_->agregarHijo(std::make_shared<Nodo>(siguienteId_++, nombre, TipoNodo::Archivo, contenido)); }
std::vector<std::string> ArbolFS::ls() const { std::vector<std::string> r; for(auto& h: actual_->hijos()) r.push_back(h->nombre()); return r; }