#pragma once
#include <string>
#include <memory>
#include "nodo.h"

std::string serializarJson(const std::shared_ptr<Nodo>& n);
std::shared_ptr<Nodo> cargarJson(const std::string& contenido);