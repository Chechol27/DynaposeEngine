#pragma once
#include "../DynaPose.h"

#include <vector>
#include <memory>

#include "tiny_gltf.h"

namespace DynaPose{
    class DynaPoseScene{
        private:
            std::shared_ptr<tinygltf::Model> parent;
            tinygltf::Scene scene;
            std::vector<std::shared_ptr<Rig>> rigs; //kept flattened in case memory contiguous implementation is needed
            std::vector<std::shared_ptr<NodeSolver>> solvers; //kept flattened in case memory contiguous implementation is needed

        public:
            DynaPoseScene(tinygltf::Scene& _scene, std::shared_ptr<tinygltf::Model> _model);
            bool Update(float deltaTime);
            bool Update(int rigIndex, float deltaTime);
    };
}
