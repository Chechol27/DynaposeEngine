#pragma once
#include "tiny_gltf.h"

namespace DynaPose
{
    ///<summary>
    ///In-engine representation for an "actor", this contains references for both the 1 to 1 node hierarchy of the
    ///In-game actor and the proxy rig that has all the solvers and modifiers
    ///<summary>
    class Rig
    {
        tinygltf::Node* gameRoot;
        tinygltf::Node* proxyRoot;
        Rig() = default;
        Rig(tinygltf::Node* _gameRoot, tinygltf::Node* _proxyRoot);
    };

}
