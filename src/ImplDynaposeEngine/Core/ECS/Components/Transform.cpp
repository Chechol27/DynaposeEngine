#include "../../../../DynaposeEngine/Core/ECS/Components/Transform.h"

#include <iostream>

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>

#include "Core/World.h"

namespace DynaPose::Components
{
    Transform::Transform(entt::entity& parent)
    {
        this->parent = parent;
        children = std::vector<entt::entity>();
        localPosition = glm::vec3(0, 0, 0);
        rotation = glm::quat(1, 0, 0, 0);
        scale = glm::vec3(1, 1, 1);
        localToWorld = glm::mat4(1);
    }

    Transform::Transform(const Transform& other)
    {
        parent = other.parent;
        localPosition = other.localPosition;
        rotation = other.rotation;
        scale = other.scale;
        children = other.children;
        localToWorld = other.localToWorld;
    }

    Transform::Transform()
    {
        parent = entt::null;
        children = std::vector<entt::entity>();
        localPosition = glm::vec3(0, 0, 0);
        rotation = glm::quat(1, 0, 0, 0);
        scale = glm::vec3(1, 1, 1);
        localToWorld = glm::mat4(1);
    }
}
