cmake_minimum_required(VERSION 3.20)
project(gpu_driver_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Drivers are toggled off by default until we implement them (Week 2+).
option(ENABLE_DRIVER_NVK "Build the NVK-inspired mock driver backend" OFF)
option(ENABLE_SOFTWARE_RENDERER "Build the CPU fallback driver" OFF)
option(BUILD_SHARED_LIBS "Build libraries as shared instead of static" OFF)
option(BUILD_TESTING "Build unit tests" ON)

add_subdirectory(core)

if(ENABLE_DRIVER_NVK)
    add_subdirectory(drivers/nvk)
endif()

if(ENABLE_SOFTWARE_RENDERER)
    add_subdirectory(drivers/software)
endif()

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
