#pragma once
#include <string>

inline std::string jsonSchema() {
    return R"({
  "id": "uint64",
  "nombre": "string",
  "tipo": "archivo|carpeta",
  "contenido": "string",
  "hijos": [ ... ]
})";
}