#include "Serialization/Serializers/TransformSerializer.h"

#include "tiny_gltf.h"

namespace DynaPoseIO
{
    void ReadTransformGraph(const tinygltf::Model& model, const tinygltf::Node& node, Transform& transform)
    {
        transform.SetPosition(glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
        transform.SetRotation(glm::quat(node.rotation[0], node.rotation[1], node.rotation[2],node.rotation[3]));
        transform.SetScale(glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
        transform.UpdateMatrix();
        for (const auto gltfNode : node.children)
        {
            Transform child;
            ReadTransformGraph(model.nodes[gltfNode], child);
        }
    }
}
