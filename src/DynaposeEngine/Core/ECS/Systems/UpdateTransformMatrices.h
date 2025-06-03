#pragma once

#include <entt/entt.hpp>
#include "ISystem.h"
#include "../Components/Transform.h"


using namespace DynaPoseComponents;
namespace DynaPoseSystems
{
    class UpdateTransformMatrices : public ISystem
    {
        public:
            static void UpdateTransformMatrix(entt::entity owner, Transform& transform);
            static void UpdateTransform(entt::entity owner, bool dirty);
            void OnUpdate(float deltaTime) override;
    };
}