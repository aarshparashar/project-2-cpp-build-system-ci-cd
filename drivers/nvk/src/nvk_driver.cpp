#include "nvk_driver/nvk_driver.h"

#include "gpu_core/plugin.h"

namespace gpu_core {

std::string NvkDriver::Name() const {
    return "nvk_driver (mock NVIDIA/Vulkan backend)";
}

bool NvkDriver::Supports(DeviceCapability capability) const {
    return capability == DeviceCapability::kGraphics || capability == DeviceCapability::kCompute;
}

}  // namespace gpu_core

// C-linkage export so dlsym() can find this by an unmangled name, mirroring
// how a real Vulkan ICD exports its entry point for the loader.
extern "C" gpu_core::Device* gpu_core_create_device() {
    return new gpu_core::NvkDriver();
}
