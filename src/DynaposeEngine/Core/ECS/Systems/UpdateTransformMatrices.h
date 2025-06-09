#pragma once

#include <entt/entt.hpp>
#include "ISystem.h"
#include "../Components/Transform.h"


using namespace DynaPose::Components;
namespace DynaPose::Systems
{
    class UpdateTransformMatrices : public ISystem
    {
        public:
            static void UpdateTransformMatrix(entt::entity owner, Transform& transform);
            static void UpdateTransform(entt::entity owner, bool dirty);
            void OnUpdate(float deltaTime) override;
            int GetPriority() override;
    };
}