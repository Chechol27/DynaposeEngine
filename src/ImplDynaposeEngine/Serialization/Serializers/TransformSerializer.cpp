#include "Serialization/Serializers/TransformSerializer.h"

#include <iostream>

#include "tiny_gltf.h"
#include "Core/World.h"
#include "Core/ECS/Components/TransformUtils.h"
#include "Core/ECS/Systems/UpdateTransformMatrices.h"

namespace DynaPoseIO
{
    void ReadTransformGraph(const tinygltf::Model& model, const tinygltf::Node& node, entt::entity owner, entt::entity parent, Transform& transform)
    {
        std::vector<double> translation = node.translation;
        std::vector<double> rotation = node.rotation;
        std::vector<double> scale = node.scale;

        if (translation.size() < 3)
            transform.localPosition = glm::vec3(0,0,0);
        else
            transform.localPosition = glm::vec3(translation[0], translation[1], translation[2]);
        if (rotation.size() < 4)
            transform.rotation = glm::quat(1,0,0,0);
        else
            transform.rotation = glm::quat(node.rotation[0], node.rotation[1], node.rotation[2],node.rotation[3]);
        if (scale.size() < 3)
            transform.scale = glm::vec3(1,1,1);
        else
            transform.scale = glm::vec3(node.scale[0], node.scale[1], node.scale[2]);

        transform.parent = parent;
        Systems::UpdateTransformMatrices::UpdateTransformMatrix(owner, transform);
        for (const auto gltfNode : node.children)
        {
            auto childNode = model.nodes[gltfNode];
            entt::entity childOwner = World::GetInstance()->SpawnEntity(childNode.name);
            transform.children.push_back(childOwner);
            auto& child = World::GetInstance()->GetRegistry()->emplace<Transform>(childOwner);
            ReadTransformGraph(model, childNode, childOwner, owner, child);
        }
    }
}
