// Clase Nodo: representa un elemento del sistema de archivos (archivo o carpeta)
#pragma once
#include <string>
#include <vector>
#include <memory>

enum class TipoNodo { Archivo, Carpeta };

class Nodo {
private:
    std::uint64_t id_;
    std::string nombre_;
    TipoNodo tipo_;
    std::string contenido_;
    std::vector<std::shared_ptr<Nodo>> hijos_;
    std::weak_ptr<Nodo> padre_;

public:
    Nodo(std::uint64_t id, std::string nombre, TipoNodo tipo, std::string contenido = "");

    std::uint64_t id() const;
    const std::string& nombre() const;
    TipoNodo tipo() const;
    const std::string& contenido() const;
    void setContenido(const std::string& contenido);

    std::shared_ptr<Nodo> padre() const;
    void setPadre(const std::shared_ptr<Nodo>& padre);

    const std::vector<std::shared_ptr<Nodo>>& hijos() const;
    bool agregarHijo(const std::shared_ptr<Nodo>& hijo);
    bool eliminarHijoPorNombre(const std::string& nombre);
    std::shared_ptr<Nodo> buscarHijoPorNombre(const std::string& nombre) const;
};