#include <iostream>
#include "arbol_fs.h"

int main() {
    ArbolFS fs;
    fs.mkdir("docs"); fs.touch("readme.txt", "hola"); fs.touch("data.csv", "1,2,3");
    for (auto& s : fs.searchPrefix("d")) std::cout << s << "\n";
    auto exact = fs.searchExact("readme.txt"); std::cout << exact.size() << "\n";
    return 0;
}