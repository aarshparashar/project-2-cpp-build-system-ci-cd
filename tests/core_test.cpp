#include <gtest/gtest.h>

#include "gpu_core/command_buffer.h"
#include "gpu_core/shader_ir.h"

TEST(CommandBufferTest, RecordAppendsCommand) {
    gpu_core::CommandBuffer buffer;
    buffer.Record({gpu_core::CommandType::kDraw, {1, 2, 3}});

    ASSERT_EQ(buffer.Commands().size(), 1u);
    EXPECT_EQ(buffer.Commands()[0].type, gpu_core::CommandType::kDraw);
    EXPECT_EQ(buffer.Commands()[0].args, (std::vector<uint32_t>{1, 2, 3}));
}

TEST(CommandBufferTest, ResetClearsCommands) {
    gpu_core::CommandBuffer buffer;
    buffer.Record({gpu_core::CommandType::kBarrier, {}});
    buffer.Reset();

    EXPECT_TRUE(buffer.Commands().empty());
}

TEST(ShaderIRTest, AddInstructionTracksCount) {
    gpu_core::ShaderIR ir;
    ir.AddInstruction({"OpLoad", {4}});
    ir.AddInstruction({"OpStore", {4, 5}});

    EXPECT_EQ(ir.InstructionCount(), 2u);
    EXPECT_EQ(ir.Instructions()[1].opcode, "OpStore");
}
