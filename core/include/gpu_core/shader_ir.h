#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace gpu_core {

// A deliberately simplified stand-in for a real IR (e.g. SPIR-V words) — just
// enough structure for the shader_compiler tool to produce and for drivers to
// consume, without modeling actual SPIR-V binary encoding.
struct ShaderInstruction {
    std::string opcode;
    std::vector<uint32_t> operands;
};

class ShaderIR {
public:
    void AddInstruction(ShaderInstruction instruction);

    const std::vector<ShaderInstruction>& Instructions() const { return instructions_; }
    size_t InstructionCount() const { return instructions_.size(); }

private:
    std::vector<ShaderInstruction> instructions_;
};

}  // namespace gpu_core
