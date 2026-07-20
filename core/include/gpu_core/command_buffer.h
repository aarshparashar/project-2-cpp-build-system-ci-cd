#pragma once

#include <cstdint>
#include <vector>

namespace gpu_core {

enum class CommandType {
    kBindPipeline,
    kDraw,
    kDispatch,
    kBarrier,
};

struct Command {
    CommandType type;
    std::vector<uint32_t> args;
};

// Records a sequence of GPU commands prior to submission, mirroring Vulkan's
// command buffer recording model (vkCmd* calls accumulate before
// vkQueueSubmit).
class CommandBuffer {
public:
    void Record(Command command);
    void Reset();

    const std::vector<Command>& Commands() const { return commands_; }

private:
    std::vector<Command> commands_;
};

}  // namespace gpu_core
