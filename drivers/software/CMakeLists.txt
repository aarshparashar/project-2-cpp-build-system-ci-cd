add_library(software_rasterizer
    src/software_rasterizer.cpp
)

target_include_directories(software_rasterizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(software_rasterizer PUBLIC gpu_core)
