# C++ Build System & CI/CD Demo

This project demonstrates a production-grade, modular C++ build system using CMake and Ninja. It simulates a simplified GPU driver stack inspired by Mesa (e.g., NVK/Nouveau), focusing specifically on advanced build orchestration, plugin architecture, and reproducible CI/CD pipelines.

## Architecture

The project consists of the following modules:

1.  **Core Layer (`libgpu_core`)**: The foundational C++ library defining the device interface, command buffer abstraction, and shader intermediate representation.
2.  **Driver Backends (`plugins`)**:
    *   `nvk_like_driver`: A mock hardware driver plugin.
    *   `software_rasterizer`: A mock CPU fallback driver plugin.
3.  **Shader Toolchain**: A custom CLI tool that acts as a fake shader compiler (simulating `.glsl` to `.spv` compilation), integrated into the build process using CMake's `add_custom_command`.

## Build System Focus

The core objective of this repository is the build orchestration:
*   **Modern CMake**: Utilizing `target_link_libraries`, interface libraries, and clean module boundaries.
*   **Generators**: Optimized for Ninja (`-G Ninja`) for fast, parallel, and incremental builds.
*   **DevOps Features**: Integrates ccache, compile commands export (`compile_commands.json`), and dynamic loading of driver plugins.

## Building the Project

Ensure you have `cmake`, `ninja-build`, and a modern C++ compiler installed (GCC/Clang).

```bash
# Configure the project
cmake -G Ninja -B build -DENABLE_DRIVER_NVK=ON -DENABLE_SOFTWARE_RENDERER=ON

# Build the project
cmake --build build
```

## CI/CD Pipeline

The repository includes GitHub Actions workflows demonstrating:
*   Matrix builds across different compilers (GCC/Clang) and build types (Debug/Release).
*   Automated unit testing (GoogleTest/Catch2).
*   Dependency caching.
*   Artifact generation and publishing.
