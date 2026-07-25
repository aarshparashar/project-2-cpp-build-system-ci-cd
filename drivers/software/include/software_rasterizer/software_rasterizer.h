#pragma once

#include <string>

#include "gpu_core/device.h"

namespace gpu_core {

// CPU fallback backend — always available, used in headless/CI environments
// where no real (or mock) GPU driver is present.
class SoftwareRasterizer : public Device {
public:
    std::string Name() const override;
    bool Supports(DeviceCapability capability) const override;
};

}  // namespace gpu_core
