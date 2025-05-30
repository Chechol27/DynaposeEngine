#include <filesystem>
#include <gtest/gtest.h>
#include <Serialization/DynaPoseSerialization.h>
#include <Core/World.h>

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

TEST(DynaPose, DeserializeScene)
{
    auto testFilePath = GetTestFile("RigifyMetaRigBasic.glb");

    tinygltf::Model model;
    bool okGLTF = DynaPoseIO::LoadGLTF(testFilePath, model);
    ASSERT_TRUE(okGLTF);
    DynaPose::World* world = DynaPose::World::GetInstance();
    std::cout << "World loaded" << std::endl;
    world->LoadScene(model, 0);
}