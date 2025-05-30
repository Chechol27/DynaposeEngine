#include "Serialization/Serializers/TransformSerializer.h"

#include <iostream>

#include "tiny_gltf.h"

namespace DynaPoseIO
{
    void ReadTransformGraph(const tinygltf::Model& model, const tinygltf::Node& node, Transform& transform)
    {
        std::vector<double> translation = node.translation;
        std::vector<double> rotation = node.rotation;
        std::vector<double> scale = node.scale;
        if (translation.size() < 3)
            transform.SetPosition(glm::vec3(0,0,0));
        else
            transform.SetPosition(glm::vec3(translation[0], translation[1], translation[2]));
        if (rotation.size() < 4)
            transform.SetRotation(glm::quat(1,0,0,0));
        else
            transform.SetRotation(glm::quat(node.rotation[0], node.rotation[1], node.rotation[2],node.rotation[3]));
        if (scale.size() < 3)
            transform.SetScale(glm::vec3(1,1,1));
        else
            transform.SetScale(glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
        transform.UpdateMatrix();
        for (const auto gltfNode : node.children)
        {
            Transform child;
            ReadTransformGraph(model, model.nodes[gltfNode], child);
        }
    }
}
