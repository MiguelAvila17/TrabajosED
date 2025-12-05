#include <iostream>
#include "arbol_fs.h"

int main() {
    ArbolFS fs;
    fs.mkdir("docs");
    fs.touch("readme.txt", "hola");
    fs.save("filesystem.json");
    ArbolFS fs2; fs2.load("filesystem.json");
    for (auto& n : fs2.ls()) std::cout << n << "\n";
    return 0;
}