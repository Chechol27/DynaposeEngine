#pragma once

#include <entt/entt.hpp>
#include "Core/ECS/Systems/WriteGameData.h"
#include "Core/World.h"
#include "Core/InterfaceData.h"
#include "Core/ECS/Systems/SystemStage.h"

namespace DynaPose::Systems
{
    REGISTER_SYSTEM(WriteGameData, true)

    int WriteGameData::GetPriority()
    {
        return static_cast<int>(SystemStage::WriteInGameTransforms);
    }

    void WriteGameData::OnUpdate(float deltaTime)
    {
        entt::registry* registry = World::GetInstance()->GetRegistry();
        auto view = registry->view<Components::InGameEntity>();
        for (const auto& entityTransformPair : view.each())
        {
            entt::entity entity = std::get<0>(entityTransformPair);
            Components::InGameEntity& inGameEntity = std::get<1>(entityTransformPair);
            rawTransformData[inGameEntity] = registry->get<Components::Transform>(entity);
        }
    }
}
