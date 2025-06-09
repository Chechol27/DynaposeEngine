#pragma once

#define REGISTER_SYSTEM(systemType, autoStart) static_assert(std::is_base_of<ISystem, systemType>::value, "Invalid system type"); \
    static std::shared_ptr<systemType> System_##systemType = DynaPose::World::GetInstance()->RegisterSystem<systemType>(autoStart);
namespace DynaPose::Systems
{
    //TODO: Implement system requirements or priority ordering
    class ISystem
    {
    public:
        bool isStopped = false;
        virtual ~ISystem() = default;
        ///Priority for calling order
        ///Read data: 0
        ///Apply Solvers: 100
        ///Write data: 200
        ///Apply transforms: 300
        virtual int GetPriority() = 0;
        virtual void OnStartRunning();
        virtual void OnUpdate(float deltaTime);
        virtual void OnStopRunning();
        virtual void OnRemove();
    };
}