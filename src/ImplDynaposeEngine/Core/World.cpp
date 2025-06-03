#include "Core/World.h"

#include <format>
#include <iostream>
#include "Core/ECS/Components/Name.h"
#include "Serialization/Serializers/TransformSerializer.h"
#include "Core/ECS/Components/Transform.h"


using namespace DynaPoseComponents;
namespace DynaPose
{
    World::World()
    {
        registry = entt::registry{};
    }

    World* World::GetInstance()
    {
        static World instance{};
        return &instance;
    }

    void World::LoadScene(const tinygltf::Model& model, int sceneId)
    {
        Flush();
        const tinygltf::Scene& sceneObj = model.scenes[sceneId];
        for (const auto& node : sceneObj.nodes)
        {
            const tinygltf::Node& modelNode = model.nodes[node];
            entt::entity entity = SpawnEntity(modelNode.name);
            auto& loadedTransform = registry.emplace<Transform>(entity);
            DynaPoseIO::ReadTransformGraph(model, modelNode, entity, entt::null, loadedTransform);
        }
        bool test = false;
    }

    void World::Flush()
    {
        registry.clear();
    }

    entt::entity World::SpawnEntity(const std::string& name)
    {
        const entt::entity entity = registry.create();
        auto& entityName = registry.emplace<Name>(entity);
        entityName.name = name;
        return entity;
    }

    bool World::EntityValid(entt::entity entity)
    {
        return registry.valid(entity);
    }

    entt::entity World::GetEntity(const std::string& name)
    {
        auto nameView = registry.view<Name>();
        for (const auto& entityName : nameView.each())
        {
            Name nameData = std::get<1>(entityName);
            if (nameData.name == name)
            {
                return std::get<0>(entityName);
            }
        }
        return entt::null;
    }

    entt::registry* World::GetRegistry()
    {
        return &registry;
    }

    void World::UpdateSystems(float deltaTime)
    {
        for (const auto& system : systems)
        {
            if (system->isStopped) continue;
            system->OnUpdate(deltaTime);
        }
    }
}
