add_executable(nvk_plugin_smoke_test plugin_smoke_test.cpp)

target_link_libraries(nvk_plugin_smoke_test PRIVATE gpu_core ${CMAKE_DL_LIBS})

# Deliberately does NOT link nvk_driver — it dlopen()s the built artifact by
# path instead, so we still need an explicit build dependency to guarantee
# the .so exists before this test runs.
target_compile_definitions(nvk_plugin_smoke_test PRIVATE
    NVK_DRIVER_PATH="$<TARGET_FILE:nvk_driver>"
)
add_dependencies(nvk_plugin_smoke_test nvk_driver)

add_test(NAME NvkDriverPluginSmokeTest COMMAND nvk_plugin_smoke_test)
