#pragma once
#include "ISystem.h"

namespace DynaPose::Systems
{
    class ApplyDriverNodeTransformations : public ISystem
    {
    public:
        int GetPriority() override;
        void OnUpdate(float deltaTime) override;
    };
}
