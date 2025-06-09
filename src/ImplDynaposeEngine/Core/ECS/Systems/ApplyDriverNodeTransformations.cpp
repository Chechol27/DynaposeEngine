#include "Core/ECS/Systems/ApplyDriverNodeTransformations.h"
#include "Core/World.h"
#include "Core/ECS/Components/DriverNode.h"
#include "Core/ECS/Components/TransformUtils.h"
#include "Core/ECS/Systems/SystemStage.h"

namespace DynaPose::Systems
{
    REGISTER_SYSTEM(ApplyDriverNodeTransformations, true);

    int ApplyDriverNodeTransformations::GetPriority()
    {
        return static_cast<int>(SystemStage::ApplyDriverNodeTransformations); // After updating transform matrices regularly, this system overrides original transforms
    }

    void ApplyDriverNodeTransformations::OnUpdate(float deltaTime)
    {
        entt::registry* registry = World::GetInstance()->GetRegistry();
        auto view = registry->view<DriverNode>();
        for (auto viewPair : view.each())
        {
            entt::entity entity = std::get<0>(viewPair);
            DriverNode driverNode = std::get<1>(viewPair);
            Transform& driverTransform = registry->get<Transform>(entity);

            for (auto& driver : driverNode.driverData)
            {
                entt::entity drivenEntity = std::get<0>(driver);
                Transform& drivenTransform = registry->get<Transform>(drivenEntity);
                TransformUtils::UpdateMatrixAsChild(drivenTransform, driverTransform);
            }
        }
    }
}
