#include <iostream>
#include <fstream>
#include <sstream>
#include "arbol_fs.h"

int main(){
    ArbolFS fs;
    std::ifstream f("commands.txt");
    std::string line; while (std::getline(f,line)) {
        std::istringstream iss(line); std::string cmd; iss >> cmd; 
        if (cmd=="mkdir") { std::string n; iss>>n; fs.mkdir(n);} 
        else if (cmd=="touch") { std::string n; iss>>n; std::string c; std::getline(iss,c); if(!c.empty()&&c[0]==' ') c.erase(0,1); fs.touch(n,c);} 
    }
    for (auto&s: fs.ls()) std::cout<<s<<"\n";
    return 0;
}