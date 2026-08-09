#include "shader_compiler/compile.h"

namespace shader_compiler {

void CompileMock(std::istream& input, std::ostream& output) {
    output << "MSPV" << '\x01';
    output << input.rdbuf();
}

}  // namespace shader_compiler
