#include "Core/ECS/Systems/UpdateTransformMatrices.h"
#include "Core/World.h"
#include "Core/ECS/Components/Transform.h"
using namespace DynaPose;
namespace DynaPoseSystems
{
    REGISTER_SYSTEM(UpdateTransformMatrices, true)

    void UpdateTransformMatrices::UpdateTransformMatrix(entt::entity owner, Transform& transform)
    {
        const glm::mat4x4 rotationMat = glm::toMat4(transform.rotation);
        transform.localToWorld = glm::scale(glm::mat4(1.0f), transform.scale) * rotationMat * glm::translate( glm::mat4(1.0f), transform.localPosition);

        if (World::GetInstance()->EntityValid(transform.parent))
        {
            auto& parentTransform = World::GetInstance()->GetComponent<Transform>(transform.parent);
            transform.localToWorld = parentTransform.localToWorld * transform.localToWorld;
        }
    }

    void UpdateTransformMatrices::UpdateTransform(entt::entity owner, bool dirty)
    {
        auto& transform = World::GetInstance()->GetComponent<Transform>(owner);
        dirty |= transform.dirty;
        if (dirty)
        {
            UpdateTransformMatrix(owner, transform);
            transform.dirty = false;
        }
        for (auto& child: transform.children)
        {
            if (!World::GetInstance()->EntityValid(child)) continue;
            UpdateTransform(child, dirty);
        }
    }

    void UpdateTransformMatrices::OnUpdate(float deltaTime)
    {
        auto transformView = World::GetInstance()->GetRegistry()->view<Transform>();
        for (auto viewPair : transformView.each())
        {
            UpdateTransform(std::get<0>(viewPair), true);
        }
    }
}