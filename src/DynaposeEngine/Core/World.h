#pragma once
#include <memory>
#include <vector>

#include "tiny_gltf.h"
#include "Transform.h"

namespace DynaPose
{
    class World
    {
    private:
        World() = default;
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;

        std::unique_ptr<tinygltf::Model> currentModel;

        std::vector<std::shared_ptr<Transform>> transforms{};

    public:
        static World* GetInstance();

        void LoadScene(const tinygltf::Model& model, int sceneId);
        void Update();
        void Flush();

        unsigned long long GetObjectCount();
    };
}
