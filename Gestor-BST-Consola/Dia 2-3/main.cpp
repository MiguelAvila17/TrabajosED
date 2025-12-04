#include <iostream>
#include "arbol_fs.h"
void run_tests();

int main() {
    run_tests();
    ArbolFS fs;
    fs.mkdir("docs");
    fs.touch("readme.txt", "Proyecto 123");
    for (auto& n : fs.ls()) std::cout << n << "\n";
    return 0;
}