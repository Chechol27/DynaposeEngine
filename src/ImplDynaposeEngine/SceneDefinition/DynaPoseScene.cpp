#include <format>
#include "tiny_gltf.h"
#include "SceneDefinition/DynaPoseScene.h"
#include "Serialization/DynaPoseSerialization.h"
#include "Rigs/Rig.h"

namespace DynaPose
{
    DynaPoseScene::DynaPoseScene(tinygltf::Scene& _scene, std::shared_ptr<tinygltf::Model> _model)
    {
        scene = _scene;
        //Initialize rigs and solvers
        auto it = scene.extensions.find(DYNAPOSE_GLTF_EXTENSION);
        if (it == scene.extensions.end())
        {
            throw std::runtime_error(std::format("Scene schema error: DynaPose extension ({}) not found in GLTF scene", DYNAPOSE_GLTF_EXTENSION));
        }

        const tinygltf::Value& dynaPoseData = it->second;

        //Rigs
        const tinygltf::Value& rigData = dynaPoseData.Get("Rigs");
        if (!rigData.IsArray())
        {
            throw std::runtime_error("Rig data malformed in GLTF scene, it is supposed to be an array");
        }
        for (const auto& rig : rigData.Get<std::vector<tinygltf::Value>>())
        {
            const int& gameRootId = rig.Get("gameRoot").GetNumberAsInt();
            const int& proxyRootId = rig.Get("proxyRoot").GetNumberAsInt();
            const tinygltf::Node* node = &_model.nodes[gameRootId];
        }
    }
}
