#pragma once
#include "DynaPose.h"
#include "tiny_gltf.h"
#include "Core/Transform.h"

using namespace DynaPose;
namespace DynaPoseIO
{
    void ReadTransformGraph(const tinygltf::Node& node, Transform& transform);
}