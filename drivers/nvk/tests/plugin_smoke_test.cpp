#include <dlfcn.h>

#include <cstdio>
#include <cstring>

#include "gpu_core/device.h"
#include "gpu_core/plugin.h"

// Loads the built nvk_driver.so at runtime (NVK_DRIVER_PATH is injected by
// CMake) exactly the way a real driver loader would, instead of linking
// against nvk_driver directly. This is the test that actually proves the
// plugin contract works end-to-end, not just that the class compiles.
int main() {
    void* handle = dlopen(NVK_DRIVER_PATH, RTLD_NOW);
    if (!handle) {
        std::fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    auto create_device =
        reinterpret_cast<gpu_core::CreateDeviceFn>(dlsym(handle, gpu_core::kCreateDeviceSymbol));
    if (!create_device) {
        std::fprintf(stderr, "dlsym failed: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    gpu_core::Device* device = create_device();
    bool ok = device->Supports(gpu_core::DeviceCapability::kCompute) &&
              std::strstr(device->Name().c_str(), "nvk") != nullptr;

    if (!ok) {
        std::fprintf(stderr, "loaded device failed sanity checks: name=%s\n",
                      device->Name().c_str());
    }

    delete device;
    dlclose(handle);

    return ok ? 0 : 1;
}
