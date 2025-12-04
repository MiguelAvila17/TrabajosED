#pragma once
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include "nodo.h"

class ArbolFS {
    std::shared_ptr<Nodo> raiz_;
    std::shared_ptr<Nodo> actual_;
    std::uint64_t siguienteId_;
public:
    ArbolFS();
    bool mkdir(const std::string& nombre);
    bool touch(const std::string& nombre, const std::string& contenido);
    std::vector<std::string> ls() const;
};