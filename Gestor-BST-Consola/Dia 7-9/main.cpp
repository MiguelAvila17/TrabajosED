#include <iostream>
#include <sstream>
#include "arbol_fs.h"

int main(){
    ArbolFS fs;
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        std::istringstream iss(line); std::string cmd; iss >> cmd;
        if (cmd=="exit"||cmd=="quit") break;
        else if (cmd=="mkdir") { std::string nombre; iss >> nombre; std::cout << (fs.mkdir(nombre)?"ok":"err") << "\n"; }
        else if (cmd=="touch") { std::string nombre, contenido; iss >> nombre; std::getline(iss, contenido); if(!contenido.empty()&&contenido[0]==' ') contenido.erase(0,1); std::cout << (fs.touch(nombre, contenido)?"ok":"err") << "\n"; }
        else if (cmd=="ls") { for (auto& n: fs.ls()) std::cout << n << "\n"; }
        else if (cmd=="mv") { std::string nombre, destino; iss >> nombre >> destino; std::cout << (fs.mv(nombre, destino)?"ok":"err") << "\n"; }
        else if (cmd=="rm") { std::string nombre; iss >> nombre; std::cout << (fs.rm(nombre)?"ok":"err") << "\n"; }
        else if (cmd=="search") { std::string pref; iss >> pref; for (auto& s: fs.searchPrefix(pref)) std::cout << s << "\n"; }
        else if (cmd=="export") { std::vector<std::string> out; fs.exportPreorden(out); for(auto& s: out) std::cout << s << "\n"; }
        else if (cmd=="size") { std::cout << fs.size() << "\n"; }
        else if (cmd=="height") { std::cout << fs.height() << "\n"; }
        else { std::cout << "cmd?\n"; }
    }
    return 0;
}