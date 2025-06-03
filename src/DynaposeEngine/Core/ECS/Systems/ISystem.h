#pragma once

#define REGISTER_SYSTEM(systemType, autoStart) static_assert(std::is_base_of<ISystem, systemType>::value, "Invalid system type"); \
    static std::shared_ptr<systemType> System_##systemType = DynaPose::World::GetInstance()->RegisterSystem<systemType>(autoStart);
namespace DynaPoseSystems
{
    class ISystem
    {
    public:
        bool isStopped = false;
        virtual ~ISystem() = default;
        virtual void OnStartRunning();
        virtual void OnUpdate(float deltaTime);
        virtual void OnStopRunning();
        virtual void OnRemove();
    };
}