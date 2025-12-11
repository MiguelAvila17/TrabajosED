#include <iostream>
#include <chrono>
#include "arbol_fs.h"

int main(){
    ArbolFS fs;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i=0;i<5000;++i) fs.mkdir("dir"+std::to_string(i));
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "mk: " << std::chrono::duration<double, std::milli>(t1-t0).count() << "ms\n";
    std::cout << fs.ls().size() << "\n";
    return 0;
}