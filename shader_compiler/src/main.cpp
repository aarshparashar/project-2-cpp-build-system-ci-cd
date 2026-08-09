#include <fstream>
#include <iostream>

#include "shader_compiler/compile.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: shader_compiler <input.glsl> <output.spv>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2], std::ios::binary);
    if (!input || !output) {
        std::cerr << "failed to open input/output file\n";
        return 1;
    }

    shader_compiler::CompileMock(input, output);
    return 0;
}
