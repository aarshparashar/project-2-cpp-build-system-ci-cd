#include <gtest/gtest.h>

#include <sstream>

#include "shader_compiler/compile.h"

TEST(ShaderCompilerTest, PrependsMockHeaderAndCopiesInput) {
    std::istringstream input("hello");
    std::ostringstream output;

    shader_compiler::CompileMock(input, output);

    std::string result = output.str();
    EXPECT_EQ(result.substr(0, 4), "MSPV");
    EXPECT_EQ(result.substr(5), "hello");
}
