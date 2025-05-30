#include "Serialization/DynaPoseSerialization.h"

#include <filesystem>

#include "tiny_gltf.h"
namespace DynaPoseIO
{
    bool LoadGLTF(const std::filesystem::path& filePath, tinygltf::Model& model)
    {
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        bool isBinary(filePath.extension() == ".glb");
        bool ret = false;
        if (isBinary)
        {
            ret = loader.LoadBinaryFromFile(&model, &err, &warn, filePath.string(), tinygltf::REQUIRE_NODES);
        }
        else
        {
            ret = loader.LoadASCIIFromFile(&model, &err, &warn, filePath.string(), tinygltf::REQUIRE_NODES);
        }

        if (!err.empty())
        {

        }

        return ret;
    }

    void SaveGLTF(const std::filesystem::path& filePath, const tinygltf::Model& model)
    {
    }
}
