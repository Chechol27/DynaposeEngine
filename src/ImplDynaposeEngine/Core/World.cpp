#include "Core/World.h"
#include "Serialization/Serializers/TransformSerializer.h"

namespace DynaPose
{
    World* World::GetInstance()
    {
        static World instance;
        return &instance;
    }

    void World::LoadScene(const tinygltf::Model model, int sceneId)
    {
        Flush();
        const tinygltf::Scene& sceneObj = model.scenes[sceneId];
        for (const auto& node : sceneObj.nodes)
        {
            Transform loadedTransform;
            DynaPoseIO::ReadTransformGraph(model.nodes[node], loadedTransform);
            transforms.push_back(std::make_shared<Transform>(loadedTransform));
        }
    }

    void World::Update()
    {
        //Update all solvers
        for (const auto& transform : transforms)
        {
            if (!transform->GetParent())
                transform->Update(true);
        }
    }

    void World::Flush()
    {
        transforms.clear();
    }
}
