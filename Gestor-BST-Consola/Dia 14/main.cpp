#include <iostream>
#include "arbol_fs.h"
int main(){ ArbolFS fs; fs.mkdir("docs"); fs.touch("readme.txt","hola"); for(auto&s:fs.ls()) std::cout<<s<<"\n"; return 0; }