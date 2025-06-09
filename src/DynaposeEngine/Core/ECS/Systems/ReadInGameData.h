#pragma once
#include "ISystem.h"

namespace DynaPose::Systems
{
    ///First stage of the engine update, reads the In-game interface database, updates the in-engine rigs and the driver
    ///rigs based on in-game data
    class ReadInGameData : public  ISystem
    {
    public:
        void OnUpdate(float deltaTime) override;
        int GetPriority() override;
    };
}
