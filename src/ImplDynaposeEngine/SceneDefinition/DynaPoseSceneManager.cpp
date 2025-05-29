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
            std::shared_ptr<tinygltf::Model> modelPtr = std::make_shared<tinygltf::Model>(model);
            models.push_back(modelPtr);
            for (auto& scene : model.scenes)
            {
                DynaPoseScene dynaPoseScene(scene, modelPtr);
                scenes.push_back(std::make_shared<DynaPoseScene>(dynaPoseScene));
            }

        }

        return ret;
    }
} // DynaPose