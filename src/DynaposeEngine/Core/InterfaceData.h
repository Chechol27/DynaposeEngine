#pragma once
#include <unordered_map>

#include "json.hpp"
#include <entt/entt.hpp>

#include "ECS/Components/InGameEntity.h"
#include "ECS/Components/Transform.h"

namespace DynaPose
{
    /**
     * Interface data pool for raw transform data, used by games to write their data using
     * hashes as
     */
    static std::map<Components::InGameEntity, Components::Transform> rawTransformData;
    static std::map<Components::InGameEntity, nlohmann::json> arbitraryData;

    ///Used for writing data in the engine's transform data pool in order to preserve game to engine node synchronization
    void WriteRawData(std::map<Components::InGameEntity, Components::Transform> _rawTransformData);

    ///Used for writing extra data in the engine's arbitrary data pool, used to configure specific solver
    void WriteArbitraryData(std::map<Components::InGameEntity, nlohmann::json> _arbitraryData);
}
