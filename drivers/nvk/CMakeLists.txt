add_library(nvk_driver SHARED
    src/nvk_driver.cpp
)

target_include_directories(nvk_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(nvk_driver PUBLIC gpu_core)

gpu_driver_stack_enable_warnings(nvk_driver)

# Mirrors real driver .so versioning scheme:
#   libnvk_driver.so -> libnvk_driver.so.0 -> libnvk_driver.so.0.1.0
# VERSION is the full release version; SOVERSION is the ABI-compatibility
# version consumers link against (bump it only on breaking ABI changes).
set_target_properties(nvk_driver PROPERTIES
    VERSION 0.1.0
    SOVERSION 0
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
