#pragma once

#include <string>

#include "gpu_core/device.h"

namespace gpu_core {

// Mock NVK-inspired backend — simulates NVIDIA-style Vulkan command
// submission without touching any real hardware or kernel driver.
class NvkDriver : public Device {
public:
    std::string Name() const override;
    bool Supports(DeviceCapability capability) const override;
};

}  // namespace gpu_core
