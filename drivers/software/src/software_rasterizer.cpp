#include "software_rasterizer/software_rasterizer.h"

namespace gpu_core {

std::string SoftwareRasterizer::Name() const {
    return "software_rasterizer (CPU fallback)";
}

bool SoftwareRasterizer::Supports(DeviceCapability capability) const {
    return capability == DeviceCapability::kGraphics;
}

}  // namespace gpu_core
