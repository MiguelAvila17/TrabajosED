#include <cassert>
#include "arbol_fs.h"

void run_tests() {
    ArbolFS fs;
    assert(fs.mkdir("docs"));
    assert(!fs.mkdir("docs"));
    assert(fs.touch("readme.txt", "hi"));
}