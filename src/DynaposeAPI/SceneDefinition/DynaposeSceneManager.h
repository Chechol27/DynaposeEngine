//
// Created by Sergio on 26/05/2025.
//

#pragma once

#include <memory>
#include <vector>

namespace DynaPose {

    class DynaposeSceneManager {
        private:
            std::vector<std::shared_ptr<gltf::Scene>> scenes;
        public:
            bool LoadScene(const std::string& scenePath);

    };

} // DynaPose

