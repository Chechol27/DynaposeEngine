#pragma once
#include "ISystem.h"

namespace DynaPose::Systems
{
    ///Final Stage of the engine, applies proxy data to rig data and fills the in-game interface database with update
    ///infirmation
    class WriteGameData : public ISystem
    {
    public:
        int GetPriority() override;
        void OnUpdate(float deltaTime) override;
    };
}
