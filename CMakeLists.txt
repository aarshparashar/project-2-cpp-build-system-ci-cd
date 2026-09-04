cmake_minimum_required(VERSION 3.20)
project(gpu_driver_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
include(CompilerWarnings)

# Auto-detect ccache so every dev/CI invocation benefits without needing to
# remember -DCMAKE_CXX_COMPILER_LAUNCHER=ccache by hand. Only applies if the
# caller hasn't already set a launcher explicitly (e.g. CI overriding it).
if(NOT CMAKE_CXX_COMPILER_LAUNCHER)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        message(STATUS "ccache found, enabling as compiler launcher: ${CCACHE_PROGRAM}")
    endif()
endif()

option(ENABLE_DRIVER_NVK "Build the NVK-inspired mock driver backend" ON)
option(ENABLE_SOFTWARE_RENDERER "Build the CPU fallback driver" ON)
option(BUILD_SHARED_LIBS "Build libraries as shared instead of static" OFF)
option(BUILD_TESTING "Build unit tests" ON)

if(BUILD_TESTING)
    enable_testing()
endif()

add_subdirectory(core)
add_subdirectory(shader_compiler)

if(ENABLE_DRIVER_NVK)
    add_subdirectory(drivers/nvk)
endif()

if(ENABLE_SOFTWARE_RENDERER)
    add_subdirectory(drivers/software)
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
