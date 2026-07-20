#pragma once

#include <string>

namespace gpu_core {

enum class DeviceCapability {
    kGraphics,
    kCompute,
};

// Abstract interface every driver backend (NVK-inspired, software fallback)
// must implement, so the rest of the stack never depends on a concrete
// backend type.
class Device {
public:
    virtual ~Device() = default;

    virtual std::string Name() const = 0;
    virtual bool Supports(DeviceCapability capability) const = 0;
};

}  // namespace gpu_core