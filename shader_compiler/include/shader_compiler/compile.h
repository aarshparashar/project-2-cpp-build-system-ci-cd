#pragma once

#include <istream>
#include <ostream>

namespace shader_compiler {

// Deliberately fake "compilation": slaps a magic header + version byte onto
// the input bytes and copies them through unchanged. Just enough of an
// input -> output transformation for the build pipeline to exercise a real
// build-time codegen step — not an actual GLSL -> SPIR-V compiler.
void CompileMock(std::istream& input, std::ostream& output);

}  // namespace shader_compiler
