# C++ Build System & CI/CD — NVK-Inspired GPU Driver Stack

This project demonstrates a production-grade, modular C++ build system using CMake and Ninja. It simulates a simplified GPU driver stack inspired by **NVK** — Mesa's modern open-source Vulkan driver for NVIDIA hardware — focusing specifically on advanced build orchestration, plugin architecture, and reproducible CI/CD pipelines.

**Note on scope:** this is NVK-*inspired*, not an attempt to reimplement real NVK (a serious, large production driver maintained by the Mesa project). The mock Device/CommandBuffer/ShaderIR/driver-plugin code here exists only to give the build system, CI matrix, and sanitizer/packaging pipeline something real to compile, test, and ship — the transferable skill this repo demonstrates is the build/CI/CD engineering, not the driver internals themselves.

## Architecture

The project consists of the following modules:

1.  **Core Layer (`libgpu_core`)**: The foundational C++ static/shared library defining:
    *   Device interface abstraction
    *   Command buffer management
    *   Shader intermediate representation (IR)
    *   Clean API boundaries using modern CMake target-based design

2.  **Driver Backend (`nvk_driver`)**: A dynamically loadable mock driver plugin inspired by NVK's architecture:
    *   Registered via a plugin interface
    *   Simulates NVIDIA-style Vulkan command submission
    *   Built as a separate shared library with its own CMake target

3.  **Software Fallback (`software_rasterizer`)**: A CPU-based fallback driver for headless/CI environments, ensuring the full pipeline is testable without a GPU.

4.  **Shader Toolchain**: A custom CLI tool acting as a fake shader compiler:
    *   Converts `.glsl` → `.spv` (mock SPIR-V transformation)
    *   Integrated via CMake `add_custom_command`
    *   Outputs tracked as versioned build artifacts

## Build System Focus

The core objective of this repository is build orchestration — demonstrating skills directly relevant to NVIDIA/GPU driver development workflows:

*   **Modern CMake**: `target_link_libraries`, interface libraries, and strict module boundaries — no global includes or variables
*   **Ninja Generator**: `-G Ninja` for fast, parallel, and truly incremental builds
*   **Compile Options**:
    *   `ENABLE_DRIVER_NVK` — toggle the NVK-inspired backend
    *   `ENABLE_SOFTWARE_RENDERER` — toggle the CPU fallback
    *   `BUILD_SHARED_LIBS` — control static vs shared linking
*   **DevOps Features**: automatic ccache detection (no manual flag needed), `compile_commands.json` export for IDE/LSP support, a build-time profiling script (`scripts/report_build_times.sh`) that surfaces the slowest compile steps from Ninja's build log

## Building the Project

Ensure you have `cmake`, `ninja-build`, `ccache`, and a modern C++ compiler (GCC ≥ 12 or Clang ≥ 16).

```bash
# Configure — NVK backend ON, software renderer as fallback. ccache is
# auto-detected and enabled by the top-level CMakeLists.txt if present.
cmake -G Ninja -B build \
  -DENABLE_DRIVER_NVK=ON \
  -DENABLE_SOFTWARE_RENDERER=ON

# Build (parallel via Ninja)
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure

# See the slowest build steps
./scripts/report_build_times.sh build
```

## Repository Structure

```text
project-2-cpp-build-system-ci-cd/
├── core/               # libgpu_core — device interface, command buffers, shader IR
├── drivers/
│   ├── nvk/            # NVK-inspired Vulkan driver plugin (dynamically loaded .so)
│   └── software/        # CPU fallback backend (statically linked)
├── shader_compiler/    # Mock GLSL → SPIR-V CLI tool, run via add_custom_command
├── tests/              # GoogleTest unit + plugin-loading smoke tests
├── cmake/modules/      # Custom CMake find modules and helpers (e.g. CompilerWarnings)
└── scripts/            # Build, lint, and CI helper scripts
```

## CI/CD Pipeline

The repository includes a GitHub Actions workflow demonstrating:
*   **Matrix builds**: GCC and Clang × Debug and Release build types
*   **Automated testing**: unit tests per module, plus a plugin-loading smoke test that `dlopen`s the built driver `.so`
*   **Sanitizers**: a dedicated ASan+UBSan job (Debug, Clang) catching memory/UB bugs without tripling the whole matrix's runtime
*   **Warnings-as-errors**: `-Wall -Wextra -Werror` on our own targets only, never on vendored dependencies
*   **Dependency caching**: ccache and CMake dependency caching across runs
*   **Artifact publishing**: `nvk_driver` built, versioned, and packaged as its own release artifact, independent of the rest of the build

