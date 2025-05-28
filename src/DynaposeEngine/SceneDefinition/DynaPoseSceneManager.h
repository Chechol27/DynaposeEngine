#pragma once

#include <memory>
#include <vector>

#include "SceneDefinition/DynaPoseScene.h"

namespace DynaPose {

    class DynaPoseSceneManager {
        private:
            std::vector<std::shared_ptr<tinygltf::Model>> models;
            std::vector<std::shared_ptr<DynaPoseScene>> scenes;
        public:
            bool LoadScene(const std::string& scenePath);
    };

} // DynaPose

