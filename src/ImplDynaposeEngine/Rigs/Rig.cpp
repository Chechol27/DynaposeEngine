#include "Rigs/Rig.h"

namespace DynaPose
{
    Rig::Rig(tinygltf::Node* _gameRoot, tinygltf::Node* _proxyRoot)
    {
        gameRoot = _gameRoot;
        proxyRoot = _proxyRoot;
    }
}
