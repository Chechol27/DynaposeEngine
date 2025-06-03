

#include <filesystem>
#include <format>
#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Core/World.h"
#include "Serialization/DynaPoseSerialization.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/ECS/Components/TransformUtils.h"
#include <glm/gtx/string_cast.hpp>

#include "TestUtils.h"
#include "Core/ECS/Components/Name.h"

using namespace DynaPose;
using namespace DynaPoseComponents;

#define FLOAT_TEST_TOLERANCE 0.00001f

///Test overview
///test transform, position, rotation and scale and its utility functions
/// test file is a single bone hierarchy that looks like this:
///         |   <- Name: Test, Local Position: 0,1,0
///         |   <- Name: Root, Local Position: 0,0,0
///
TEST(DynaPoseECS, TestTransformUpdate)
{
    //Load Scene
    World* world = World::GetInstance();
    auto testFile = GetTestFile("MinimalTestRig.glb");
    tinygltf::Model model;
    DynaPoseIO::LoadGLTF(testFile, model);
    world->LoadScene(model, 0);
    entt::entity rootEntity = world->GetEntity("Root");

    //Test Position and rotation control
    auto& root = world->GetComponent<Transform>(rootEntity);
    root.localPosition = glm::vec3(2.0f, 0.0f, 0.0f);
    TransformUtils::SetEulerAngles(root, glm::vec3(glm::radians(90.0f),0,0));

    entt::entity childEntity = root.children[0];
    auto& child = world->GetComponent<Transform>(childEntity);

    root.dirty = true;
    world->UpdateSystems(0.0f);

    EXPECT_NEAR(2.0f, TransformUtils::GetWorldPosition(root).x, FLOAT_TEST_TOLERANCE);
    EXPECT_NEAR(0.0f, TransformUtils::GetWorldPosition(root).y, FLOAT_TEST_TOLERANCE);
    EXPECT_NEAR(0.0f, TransformUtils::GetWorldPosition(root).z, FLOAT_TEST_TOLERANCE);
    EXPECT_NEAR(2.0f, TransformUtils::GetWorldPosition(child).x, FLOAT_TEST_TOLERANCE);
    EXPECT_NEAR(0.0f, TransformUtils::GetWorldPosition(child).y, FLOAT_TEST_TOLERANCE);
    EXPECT_NEAR(1.0f, TransformUtils::GetWorldPosition(child).z, FLOAT_TEST_TOLERANCE);

    child.localPosition += glm::vec3(0.0f, 0.0f, 1.0f);
    child.dirty = true;
    world->UpdateSystems(0.0f);
    EXPECT_NEAR(-1.0f, TransformUtils::GetWorldPosition(child).y, FLOAT_TEST_TOLERANCE);
}
