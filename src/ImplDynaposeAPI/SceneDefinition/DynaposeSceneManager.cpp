//
// Created by Sergio on 26/05/2025.
//

#include "SceneDefinition/DynaposeSceneManager.h"

namespace DynaPose {
    bool DynaposeSceneManager::LoadScene(const std::string& scenePath)
    {
        gltf::Model model;
        gltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, scenePath);
        return true;
    }
} // DynaPose