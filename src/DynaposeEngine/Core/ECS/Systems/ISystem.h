#pragma once

namespace DynaPoseSystems
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void OnStart();
        virtual void OnStartRunning();
        virtual void OnUpdate();
        virtual void OnStopRunning();
        virtual void OnRemove();
    };
}