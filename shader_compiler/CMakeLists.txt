add_library(shader_compiler_lib
    src/compile.cpp
)
target_include_directories(shader_compiler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
gpu_driver_stack_enable_warnings(shader_compiler_lib)

add_executable(shader_compiler src/main.cpp)
target_link_libraries(shader_compiler PRIVATE shader_compiler_lib)
gpu_driver_stack_enable_warnings(shader_compiler)

# Demonstrates build-time codegen: run our own just-built tool on a sample
# shader, producing a versioned build artifact. DEPENDS on the shader_compiler
# target itself is what forces "build the tool" to happen before "run the
# tool" — CMake does not infer that ordering on its own for custom commands.
set(SAMPLE_SHADER ${CMAKE_CURRENT_SOURCE_DIR}/shaders/triangle.glsl)
set(SAMPLE_SPV ${CMAKE_CURRENT_BINARY_DIR}/triangle.spv)

add_custom_command(
    OUTPUT ${SAMPLE_SPV}
    COMMAND shader_compiler ${SAMPLE_SHADER} ${SAMPLE_SPV}
    DEPENDS shader_compiler ${SAMPLE_SHADER}
    COMMENT "Compiling triangle.glsl -> triangle.spv (mock)"
)

add_custom_target(compile_sample_shaders ALL DEPENDS ${SAMPLE_SPV})
