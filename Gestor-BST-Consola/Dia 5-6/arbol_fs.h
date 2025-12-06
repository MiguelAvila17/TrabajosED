#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include "nodo.h"
#include "trie.h"

class ArbolFS {
    std::shared_ptr<Nodo> raiz_;
    std::shared_ptr<Nodo> actual_;
    std::uint64_t siguienteId_;
    Trie trie_;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodo>>> index_;
public:
    ArbolFS();
    bool mkdir(const std::string& nombre);
    bool touch(const std::string& nombre, const std::string& contenido);
    std::vector<std::string> ls() const;
    std::vector<std::string> searchPrefix(const std::string& prefijo) const;
    std::vector<std::shared_ptr<Nodo>> searchExact(const std::string& nombre) const;
};