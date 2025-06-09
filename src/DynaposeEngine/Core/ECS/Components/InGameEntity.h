#pragma once

namespace DynaPose::Components
{
    ///In-engine representation of a game node, this entitiy's transform is a contextualized copy of the actual
    ///In-game node
    ///Game to Engine resolution happens in the following process:
    ///     1. the in-game actor and its node's ids (for example object name or guid, depends on the game) are hashed (happens in game)
    ///     2. using these hashes, all entities with a RigNode component that matches them are found (happens in engine)
    struct InGameEntity
    {
        size_t gameActorHash; //id-like value to identify the holding actor in the game
        size_t gameNodeHash; //id-like value to identify the holding node in the game
    };
}