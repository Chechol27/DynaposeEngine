#pragma once
#include <memory>
#include <typeindex>
#include <vector>

#include "tiny_gltf.h"
#include "ECS/Components/Transform.h"
#include "ECS/Systems/ISystem.h"
#include "entt/entt.hpp"

namespace DynaPose
{
    class Actor;

    class World
    {
    private:
        World();
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;
        entt::registry registry;
        std::unique_ptr<tinygltf::Model> currentModel;
        std::vector<std::shared_ptr<DynaPoseSystems::ISystem>> systems;
    public:
        static World* GetInstance();
        void LoadScene(const tinygltf::Model& model, int sceneId);
        void Flush();

#pragma region Entity Management
        entt::entity SpawnEntity(const std::string& name);
        bool EntityValid(entt::entity entity);
        entt::entity GetEntity(const std::string& name);
#pragma endregion

#pragma region Component Management
        template<typename T>
        T& AddComponent(entt::entity entity, T comp);
        template<typename T>
        T& GetComponent(entt::entity entity);
        entt::registry* GetRegistry();
#pragma endregion

#pragma region System Management
        template<typename T>
        std::shared_ptr<T> RegisterSystem(bool autoStart)
        {
            std::shared_ptr<T> system = std::make_shared<T>();
            systems.push_back(system);
            if (autoStart)
            {
                std::shared_ptr<DynaPoseSystems::ISystem> generalSystem = static_pointer_cast<DynaPoseSystems::ISystem>(system);
                generalSystem->isStopped = false;
                generalSystem->OnStartRunning();
            }
            return system;
        }
        template<typename T>
        bool StopSystem()
        {
            for (auto& system : systems)
            {
                std::shared_ptr<T> systemPtr = dynamic_pointer_cast<T>(system);
                if (systemPtr != nullptr)
                {
                    if (!systemPtr->isStopped)
                    {
                        systemPtr->isStopped = true;
                        systemPtr->OnStopRunning();
                        return true;
                    }
                }
            }
            return false;
        }
        template <typename T>
        bool StartSystem()
        {
            for (auto& system : systems)
            {
                std::shared_ptr<T> systemPtr = dynamic_pointer_cast<T>(system);
                if (systemPtr != nullptr)
                {
                    if (systemPtr->isStopped)
                    {
                        systemPtr->isStopped = false;
                        systemPtr->OnStartRunning();
                        return true;
                    }
                }
            }
            return false;
        }
        void UpdateSystems(float deltaTime);
#pragma endregion
    };

    template <typename T>
    T& World::AddComponent(entt::entity entity, T comp)
    {
        return registry.emplace<T>(entity, comp);
    }

    template <typename T>
    T& World::GetComponent(entt::entity entity)
    {
        return registry.get<T>(entity);
    }

    // template <typename T>
    // std::shared_ptr<T> World::RegisterSystem(bool autoStart)
    // {
    //     std::shared_ptr<T> system = std::make_shared<T>();
    //     systems.push_back(system);
    //     if (autoStart)
    //     {
    //         std::shared_ptr<DynaPoseSystems::ISystem> generalSystem = static_pointer_cast<DynaPoseSystems::ISystem>(system);
    //         generalSystem->isStopped = false;
    //         generalSystem->OnStartRunning();
    //     }
    //     return system;
    // }

    // template <typename T>
    // bool World::StopSystem()
    // {
    //     for (auto& system : systems)
    //     {
    //         std::shared_ptr<T> systemPtr = dynamic_pointer_cast<T>(system);
    //         if (systemPtr != nullptr)
    //         {
    //             if (!systemPtr->isStopped)
    //             {
    //                 systemPtr->isStopped = true;
    //                 systemPtr->OnStopRunning();
    //                 return true;
    //             }
    //         }
    //     }
    //     return false;
    // }

    // template <typename T>
    // bool World::StartSystem()
    // {
    //     for (auto& system : systems)
    //     {
    //         std::shared_ptr<T> systemPtr = dynamic_pointer_cast<T>(system);
    //         if (systemPtr != nullptr)
    //         {
    //             if (systemPtr->isStopped)
    //             {
    //                 systemPtr->isStopped = false;
    //                 systemPtr->OnStartRunning();
    //                 return true;
    //             }
    //         }
    //     }
    //     return false;
    // }
}
