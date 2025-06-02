#pragma once
#include <memory>
#include <typeindex>
#include <vector>

#include "tiny_gltf.h"
#include "ECS/Components/Transform.h"
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
    public:
        static World* GetInstance();
        void LoadScene(const tinygltf::Model& model, int sceneId);
        void Update();
        void Flush();
        entt::entity SpawnEntity(const std::string& name);
        template<typename T>
        T& AddComponent(entt::entity entity, T comp);
        template<typename T>
        T& GetComponent(entt::entity entity);
        bool EntityValid(entt::entity entity);
        unsigned long long GetObjectCount();
        entt::registry* GetRegistry();
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
}
