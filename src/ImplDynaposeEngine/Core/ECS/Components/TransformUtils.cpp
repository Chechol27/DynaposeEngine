#include "../../../../DynaposeEngine/Core/ECS/Components/TransformUtils.h"
#include "../../../../DynaposeEngine/Core/ECS/Components/Transform.h"
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
        return glm::vec4(transform.localPosition, 1) * transform.localToWorld;
    }

    void SetWorldPosition(Transform& transform, glm::vec3 position)
    {
        auto& inverseSource = transform;
        if (transform.parent != entt::null)
        {
            inverseSource = World::GetInstance()->GetComponent<Transform>(transform.parent);
        }
        transform.localPosition = GetInverseTransformMatrix(inverseSource) * glm::vec4(position, 1);
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
}
