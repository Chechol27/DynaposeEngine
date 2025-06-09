#include "Core/ECS/Systems/UpdateTransformMatrices.h"
#include "Core/World.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/ECS/Systems/SystemStage.h"

namespace DynaPose::Systems
{
    REGISTER_SYSTEM(UpdateTransformMatrices, true)

    void UpdateTransformMatrices::UpdateTransformMatrix(entt::entity owner, Transform& transform)
    {
        glm::mat4 localToWorld = glm::mat4(1.0f);
        localToWorld = glm::scale(localToWorld, transform.scale);
        localToWorld = localToWorld * glm::mat4_cast(transform.rotation);
        localToWorld = glm::translate(localToWorld, transform.localPosition);

        if (World::GetInstance()->EntityValid(transform.parent))
        {
            auto& parentTransform = World::GetInstance()->GetComponent<Transform>(transform.parent);
            localToWorld = parentTransform.localToWorld * localToWorld;
        }
        transform.localToWorld = localToWorld;
    }

    void UpdateTransformMatrices::UpdateTransform(entt::entity owner, bool dirty)
    {
        auto& transform = World::GetInstance()->GetComponent<Transform>(owner);
        dirty |= transform.dirty;
        if (dirty)
        {
            UpdateTransformMatrix(owner, transform);
            transform.dirty = false;
            for (auto& child: transform.children)
            {
                if (!World::GetInstance()->EntityValid(child)) continue;
                UpdateTransform(child, dirty);
            }
        }
    }

    void UpdateTransformMatrices::OnUpdate(float deltaTime)
    {
        auto transformView = World::GetInstance()->GetRegistry()->view<Transform>();
        for (auto viewPair : transformView.each())
        {
            Transform& transform = std::get<1>(viewPair);
            if (!transform.dirty) continue;
            entt::entity owner = std::get<0>(viewPair);
            UpdateTransform(owner, false);
        }
    }

    int UpdateTransformMatrices::GetPriority()
    {
        return static_cast<int>(SystemStage::UpdateTransformMatrices);
    }
}
