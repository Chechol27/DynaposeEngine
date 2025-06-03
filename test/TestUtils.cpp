#include "TestUtils.h"

std::filesystem::path GetTestFile(const std::string& filePath)
{
    const char* resourceDir =  std::getenv("RESOURCE_DIR");
    if (resourceDir == nullptr)
    {
        throw std::runtime_error("Resource directory not set");
    }
    auto testFilePath = std::filesystem::path(resourceDir);
    testFilePath /= filePath;
    return testFilePath;
}


