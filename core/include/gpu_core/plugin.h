#pragma once

#include "gpu_core/device.h"

namespace gpu_core {

// Every dynamically-loaded driver backend must export a C-linkage function
// with this exact name and signature, so it can be found via dlsym()
// without C++ name mangling getting in the way — mirrors how a real Vulkan
// ICD exports vk_icdGetInstanceProcAddr for the loader to find.
using CreateDeviceFn = Device* (*)();
constexpr const char* kCreateDeviceSymbol = "gpu_core_create_device";

}  // namespace gpu_core
