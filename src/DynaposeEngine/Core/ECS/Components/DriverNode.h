#pragma once

#include <entt/entt.hpp>
#include <glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace DynaPose::Components
{

    struct DriverNode
    {
        struct LocalTransform
        {
            glm::vec3 localPosition;
            glm::quat localRotation;
            glm::vec3 localScale;
        };

        std::map<entt::entity, LocalTransform> driverData;
    };
}