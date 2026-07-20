include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# Recommended by GoogleTest docs when mixing with projects that link the
# CRT dynamically; harmless no-op on macOS/Linux.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(core_tests
    core_test.cpp
)
target_link_libraries(core_tests PRIVATE gpu_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(core_tests)
