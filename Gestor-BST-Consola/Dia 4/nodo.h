#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

enum class TipoNodo { Archivo, Carpeta };

class Nodo {
    std::uint64_t id_;
    std::string nombre_;
    TipoNodo tipo_;
    std::string contenido_;
    std::vector<std::shared_ptr<Nodo>> hijos_;
public:
    Nodo(std::uint64_t id, std::string nombre, TipoNodo tipo, std::string contenido = "");
    std::uint64_t id() const;
    const std::string& nombre() const;
    TipoNodo tipo() const;
    const std::string& contenido() const;
    void setContenido(const std::string& contenido);
    const std::vector<std::shared_ptr<Nodo>>& hijos() const;
    bool agregarHijo(const std::shared_ptr<Nodo>& hijo);
};