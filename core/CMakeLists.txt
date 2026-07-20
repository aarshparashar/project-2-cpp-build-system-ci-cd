add_library(gpu_core
    src/command_buffer.cpp
    src/shader_ir.cpp
)

# PUBLIC: our own .cpp files need this to find "gpu_core/*.h", AND anyone
# who does target_link_libraries(their_target PRIVATE/PUBLIC gpu_core)
# inherits this include path automatically — no manual -I flags anywhere else.
target_include_directories(gpu_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(gpu_core PUBLIC cxx_std_17)
