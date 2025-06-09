#include "Core/ECS/Systems/ReadInGameData.h"
#include "Core/InterfaceData.h"
#include "Core/World.h"
#include "Core/ECS/Systems/SystemStage.h"

namespace DynaPose::Systems
{
    REGISTER_SYSTEM(ReadInGameData, true)
    void ReadInGameData::OnUpdate(float deltaTime)
    {
        for (auto& data : rawTransformData)
        {
            Components::InGameEntity entityAnchor = data.first;
            Components::Transform transform = data.second;
            transform.dirty = true;

            std::vector<entt::entity> entities;
            World* world = World::GetInstance();
            world->GetInGameEntities(entityAnchor, entities);
            for (auto& entity : entities)
            {
                world->GetRegistry()->replace<Components::Transform>(entity, transform);
            }
        }
    }

    int ReadInGameData::GetPriority()
    {
        return static_cast<int>(SystemStage::ReadInGameTransforms);
    }
}
