#pragma once
#define DYNAPOSE_GLTF_EXTENSION "MOD_DynaPose"
#include <filesystem>
#include <string>

#include "tiny_gltf.h"

namespace DynaPoseIO
{
    bool LoadGLTF(const std::filesystem::path& filePath, tinygltf::Model& model);
    void SaveGLTF(const std::filesystem::path& filePath, const tinygltf::Model& model);
}
