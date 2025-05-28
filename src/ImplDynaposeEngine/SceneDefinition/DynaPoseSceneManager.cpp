//
// Created by Sergio on 26/05/2025.
//


#include "../../DynaposeEngine/SceneDefinition/DynaPoseSceneManager.h"
#include "../../DynaposeEngine/SceneDefinition/DynaPoseScene.h"
#include "tiny_gltf.h"

namespace DynaPose {
    bool DynaPoseSceneManager::LoadScene(const std::string& scenePath)
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, scenePath);

        //Initialize new scene  based on this model
        if (ret)
        {
            models.push_back(std::make_shared<tinygltf::Model>());
            for (auto& scene : model.scenes)
            {
                DynaPoseScene dynaPoseScene(scene, model);
                scenes.push_back(std::make_shared<DynaPoseScene>(scene));
            }

        }

        return ret;
    }
} // DynaPose