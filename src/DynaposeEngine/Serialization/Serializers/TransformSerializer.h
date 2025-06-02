#pragma once
#include "DynaPose.h"
#include "tiny_gltf.h"
#include "Core/ECS/Components/Transform.h"

using namespace DynaPose;
using namespace DynaPoseComponents;
namespace DynaPoseIO
{
    void ReadTransformGraph(const tinygltf::Model& model, const tinygltf::Node& node, entt::entity owner, entt::entity parent, Transform& transform);
}