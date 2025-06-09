#include "Core/ECS/Components/TransformUtils.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/World.h"

using namespace DynaPose;
namespace TransformUtils
{
    bool IsRoot(const Transform& transform)
    {
        return World::GetInstance()->EntityValid(transform.parent);
    }

    glm::mat4x4 GetInverseTransformMatrix(const Transform& transform)
    {
        return glm::inverse(transform.localToWorld);
    }

    glm::vec3 GetWorldPosition(const Transform& transform)
    {
        return glm::vec3{transform.localToWorld * glm::vec4(0, 0, 0, 1)};
    }

    void SetWorldPosition(Transform& transform, glm::vec3 position)
    {
        transform.localPosition = GetInverseTransformMatrix(transform) * glm::vec4(position, 1);
    }

    void SetEulerAngles(Transform& transform, glm::vec3 euler)
    {
        transform.rotation = glm::quat(euler);
    }

    void SetParent(entt::entity target, entt::entity parent, bool maintainWorldPosition)
    {
        if (target == parent) return;

        auto& targetTransform = World::GetInstance()->GetComponent<Transform>(target);
        if (parent != entt::null)
        {
            bool isParentChild = IsChildOf(target, parent);
            if (isParentChild)
            {
                SetParent(parent, targetTransform.parent, true);
            }
            if (maintainWorldPosition)
            {
                //Set local position such that remains at world;
                glm::vec3 worldPos = GetWorldPosition(targetTransform);
                targetTransform.parent = parent;
                SetWorldPosition(targetTransform, worldPos);
            }
        }
        else
        {
            glm::vec3 worldPos = GetWorldPosition(targetTransform);
            targetTransform.parent = entt::null;
            targetTransform.localPosition = worldPos;
        }
    }

    bool IsChildOf(entt::entity allegedParent, entt::entity allegedChild)
    {
        auto& parentTransform = World::GetInstance()->GetComponent<Transform>(allegedParent);
        auto it = std::find(parentTransform.children.begin(), parentTransform.children.end(), allegedChild);
        if (it != parentTransform.children.end())
        {
            return true;
        }
        auto& childTransform = World::GetInstance()->GetComponent<Transform>(allegedChild);
        for (auto& grandChild : childTransform.children)
        {
            if (IsChildOf(allegedChild, grandChild))
            {
                return true;
            }
        }
        return false;
    }

    void GatherHierarchy(entt::registry* registry, Transform& root, std::vector<entt::entity>& entityVector)
    {
        for (auto& child : root.children)
        {
            entityVector.push_back(child);
            Transform& childTransform = registry->get<Transform>(child);
            GatherHierarchy(registry, childTransform, entityVector);
        }
    }

    void UpdateMatrixAsChild(Transform& target, Transform& parent)
    {
        glm::mat4 localToWorld = glm::mat4(1.0f);
        localToWorld = glm::scale(localToWorld, target.scale);
        localToWorld = localToWorld * glm::mat4_cast(target.rotation);
        localToWorld = glm::translate(localToWorld, target.localPosition);

        localToWorld *= parent.localToWorld;
        target.localToWorld = localToWorld;
    }

    void InterpolateTransform(Transform& a, Transform& b, float t, Transform& target)
    {
        target.localPosition = a.localPosition * t + b.localPosition * (1 - t);
        target.rotation = glm::slerp(a.rotation, b.rotation, t);
        target.scale = a.scale * t + b.scale * (1 - t);
    }
}
