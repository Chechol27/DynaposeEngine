#include <filesystem>
#include <format>
#include <gtest/gtest.h>
#include <Serialization/DynaPoseSerialization.h>
#include <Core/World.h>

#include "TestUtils.h"
#include "Core/ECS/Components/Name.h"

TEST(DynaPose, DeserializeScene)
{
    auto testFilePath = GetTestFile("RigifyMetaRigBasic.glb");

    tinygltf::Model model;
    bool okGLTF = DynaPoseIO::LoadGLTF(testFilePath, model);
    std::vector<std::string> gltfNames{};
    for (auto& node : model.nodes)
    {
        gltfNames.push_back(node.name);
    }

    ASSERT_TRUE(okGLTF);
    DynaPose::World* world = DynaPose::World::GetInstance();
    world->LoadScene(model, 0);
    std::vector<std::string> sceneNames{};
    auto nameView = world->GetRegistry()->view<DynaPoseComponents::Name>();
    for (auto name : nameView.each())
    {
        sceneNames.push_back(std::get<1>(name).name);
    }

    ASSERT_EQ(gltfNames.size(), sceneNames.size());
    for (int i = 0; i < gltfNames.size(); i++)
    {
        auto it = std::find(sceneNames.begin(), sceneNames.end(), gltfNames[i]);
        if (it == sceneNames.end())
        {
            std::cout << gltfNames[i] << std::endl;
            FAIL();
        }
    }
}