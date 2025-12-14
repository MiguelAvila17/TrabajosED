#include <iostream>
#include <sstream>
#include "arbol_fs.h"

int main(){
    const char* kAppName = "Proyecto 123 Final";
    const char* kAppVersion = "1.0.0";
    std::cout << kAppName << " v" << kAppVersion << " (" << __DATE__ << " " << __TIME__ << ")\n";
    ArbolFS fs;
    std::string line;
    while (true) {
        std::cout << fs.pwd() << " > ";
        if (!std::getline(std::cin, line)) break;
        std::istringstream iss(line); std::string cmd; iss >> cmd;
        if (cmd=="exit"||cmd=="quit") break;
        else if (cmd=="version"||cmd=="-v"||cmd=="--version") { std::cout << kAppName << " v" << kAppVersion << " (" << __DATE__ << " " << __TIME__ << ")\n"; continue; }
        else if (cmd=="help"||cmd=="ayuda"||cmd=="-h"||cmd=="--help") {
            std::cout << "Proyecto 123 Final - Sistema de Archivos (CLI)\n";
            std::cout << "Uso:\n";
            std::cout << "  mkdir <nombre>            Crea carpeta en la ruta actual\n";
            std::cout << "  touch <nombre> <contenido> Crea archivo con contenido\n";
            std::cout << "  mv <nombre> <destino>     Mueve nodo a carpeta destino\n";
            std::cout << "  rm <nombre>               Mueve nodo a papelera\n";
            std::cout << "  ls                        Lista hijos del nodo actual\n";
            std::cout << "  cd <nombre|..|/>          Cambia la carpeta actual\n";
            std::cout << "  pwd                       Muestra la ruta actual\n";
            std::cout << "  tree [/]                  Muestra el árbol con indentación\n";
            std::cout << "  search <prefijo>          Sugerencias por prefijo (Trie)\n";
            std::cout << "  export                    Recorrido en preorden\n";
            std::cout << "  save <archivo.json>       Guarda el estado en JSON\n";
            std::cout << "  load <archivo.json>       Carga el estado desde JSON\n";
            std::cout << "  size                      Número total de nodos\n";
            std::cout << "  height                    Altura del árbol\n";
            std::cout << "  help                      Muestra esta ayuda\n";
            std::cout << "  exit                      Salir\n";
            std::cout << "Ejemplos:\n";
            std::cout << "  mkdir docs\n";
            std::cout << "  touch readme.txt Hola mundo\n";
            std::cout << "  mv readme.txt docs\n";
            continue;
        }
        else if (cmd=="mkdir") { std::string nombre; iss >> nombre; std::cout << (fs.mkdir(nombre)?"ok":"err") << "\n"; }
        else if (cmd=="cd") { std::string nombre; iss >> nombre; std::cout << (fs.cd(nombre)?"ok":"err") << "\n"; }
        else if (cmd=="pwd") { std::cout << fs.pwd() << "\n"; }
        else if (cmd=="touch") { std::string nombre, contenido; iss >> nombre; std::getline(iss, contenido); if(!contenido.empty()&&contenido[0]==' ') contenido.erase(0,1); std::cout << (fs.touch(nombre, contenido)?"ok":"err") << "\n"; }
        else if (cmd=="ls") { for (auto& n: fs.ls()) std::cout << n << "\n"; }
        else if (cmd=="mv") { std::string nombre, destino; iss >> nombre >> destino; std::cout << (fs.mv(nombre, destino)?"ok":"err") << "\n"; }
        else if (cmd=="rm") { std::string nombre; iss >> nombre; std::cout << (fs.rm(nombre)?"ok":"err") << "\n"; }
        else if (cmd=="search") { std::string pref; iss >> pref; for (auto& s: fs.searchPrefix(pref)) std::cout << s << "\n"; }
        else if (cmd=="export") { std::vector<std::string> out; fs.exportPreorden(out); for(auto& s: out) std::cout << s << "\n"; }
        else if (cmd=="tree") { std::string arg; iss >> arg; std::vector<std::string> lines = (arg=="/") ? fs.treeFromRoot() : fs.tree(); for (auto& s: lines) std::cout << s << "\n"; }
        else if (cmd=="save") { std::string p; iss >> p; std::cout << (fs.save(p)?"ok":"err") << "\n"; }
        else if (cmd=="load") { std::string p; iss >> p; std::cout << (fs.load(p)?"ok":"err") << "\n"; }
        else if (cmd=="size") { std::cout << fs.size() << "\n"; }
        else if (cmd=="height") { std::cout << fs.height() << "\n"; }
        else { std::cout << "Comando no reconocido. Escribe 'help' para ayuda.\n"; }
    }
    return 0;
}