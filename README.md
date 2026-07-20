# C++ Build System & CI/CD — NVK-Inspired GPU Driver Stack

This project demonstrates a production-grade, modular C++ build system using CMake and Ninja. It simulates a simplified GPU driver stack inspired by **NVK** — Mesa's modern open-source Vulkan driver for NVIDIA hardware — focusing specifically on advanced build orchestration, plugin architecture, and reproducible CI/CD pipelines.

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
*   **DevOps Features**: ccache integration, `compile_commands.json` export for IDE/LSP support, build profiling hooks

## Building the Project

Ensure you have `cmake`, `ninja-build`, `ccache`, and a modern C++ compiler (GCC ≥ 12 or Clang ≥ 16).

```bash
# Configure — NVK backend ON, software renderer as fallback
cmake -G Ninja -B build \
  -DENABLE_DRIVER_NVK=ON \
  -DENABLE_SOFTWARE_RENDERER=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build (parallel via Ninja)
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure
```

## Repository Structure

```text
project-2-cpp-build-system-ci-cd/
├── core/               # libgpu_core — device interface, command buffers, shader IR
├── drivers/
│   └── nvk/            # NVK-inspired Vulkan driver plugin
├── shader_compiler/    # Fake GLSL → SPIR-V compiler CLI tool
├── tests/              # GoogleTest / Catch2 unit tests per module
├── cmake/modules/      # Custom CMake find modules and helpers
└── scripts/            # Build, lint, and CI helper scripts
```

## CI/CD Pipeline

The repository includes GitHub Actions workflows demonstrating:
*   **Matrix builds**: GCC and Clang × Debug and Release build types
*   **Automated testing**: Unit tests per module (core, nvk driver, shader compiler)
*   **Dependency caching**: ccache and CMake dependency caching across runs
*   **Artifact publishing**: Build outputs versioned and uploaded per run

