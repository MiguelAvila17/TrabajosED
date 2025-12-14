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
    std::vector<std::shared_ptr<Nodo>> papelera_;
public:
    ArbolFS();
    bool mkdir(const std::string& nombre);
    bool touch(const std::string& nombre, const std::string& contenido);
    bool mv(const std::string& nombre, const std::string& destino);
    bool rm(const std::string& nombre);
    std::vector<std::string> ls() const;
    std::vector<std::string> searchPrefix(const std::string& prefijo) const;
    std::vector<std::shared_ptr<Nodo>> searchExact(const std::string& nombre) const;
    void exportPreorden(std::vector<std::string>& out) const;
    bool save(const std::string& path) const;
    bool load(const std::string& path);
    std::size_t size() const;
    std::size_t height() const;
    bool cd(const std::string& nombre);
    std::string pwd() const;
    std::vector<std::string> tree() const;
    std::vector<std::string> treeFromRoot() const;
};