#pragma once
#include <memory>
#include <vector>

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtx/quaternion.hpp>
#include <entt/entt.hpp>

namespace DynaPose::Components
{
    struct Transform
    {
    public:
        entt::entity parent;
        std::vector<entt::entity> children;

        glm::vec3 localPosition{};
        glm::quat rotation{};
        glm::vec3 scale{};
        glm::mat4x4 localToWorld{};
        bool dirty = false;
        explicit Transform(entt::entity& parent);
        Transform(const Transform& other);
        Transform();
        void SetParent(entt::entity owner, entt::entity parent, bool maintainWorldPosition);
        bool IsRoot();
        entt::entity GetParent();
    };
}
