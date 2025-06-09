#include "Core/InterfaceData.h"

namespace DynaPose
{
    void WriteRawData(std::map<Components::InGameEntity, Components::Transform> _rawTransformData)
    {
        for (auto& pair : _rawTransformData)
        {
            rawTransformData.insert_or_assign(std::get<0>(pair), std::get<1>(pair));
        }
    }

    void WriteArbitraryData(std::map<Components::InGameEntity, nlohmann::json> _arbitraryData)
    {
        for (auto& pair : _arbitraryData)
        {
            arbitraryData.insert_or_assign(std::get<0>(pair), std::get<1>(pair));
        }
    }
}
