#pragma once
#include "Transform.h"

using namespace DynaPoseComponents;
namespace TransformUtils
{
    glm::mat4x4 GetInverseTransformMatrix(const Transform& transform);
    glm::vec3 GetWorldPosition(const Transform& transform);
    void SetWorldPosition(Transform& transform, glm::vec3 position);
    void SetEulerAngles(Transform& transform, glm::vec3 euler);
    bool IsRoot(entt::entity owner, const Transform& transform);
    void SetParent(entt::entity target, entt::entity parent, bool maintainWorldPosition);
    bool IsChildOf(entt::entity allegedParent, entt::entity allegedChild);
}