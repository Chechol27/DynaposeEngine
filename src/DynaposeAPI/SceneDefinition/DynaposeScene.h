#pragma once

namespace DynaPose
{
    class DynaPoseScene
    {
    private:
        gltf::Scene scene;
    public:
        static bool LoadScene();
    };
}
