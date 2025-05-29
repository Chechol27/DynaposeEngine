#pragma once
#include <memory>
#include <vector>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"


namespace DynaPose
{
    class Transform
    {
    private:
        std::shared_ptr<Transform> parent;
        std::vector<std::shared_ptr<Transform>> children;

        glm::vec3 localPosition{};
        glm::quat rotation{};
        glm::vec3 scale{};
        glm::mat4x4 localToWorld{};
        bool dirty = false;
    public:
        Transform() = default;
        Transform(const Transform& other);
        void Update(bool dirty);
        void UpdateMatrix();

        bool GetDirty();
        bool SetDirty(const bool& dirty);

        void GetLocalPosition(glm::vec3& position);
        void GetPosition(glm::vec3& position);
        void GetRotation(glm::quat& rotation);
        void GetEuler(glm::vec3& euler);
        void GetScale(glm::vec3& scale);
        void GetLocalToWorld(glm::mat4x4& localToWorld) const;
        void GetWorldToLocal(glm::mat4x4& worldToLocal);
        std::vector<std::shared_ptr<Transform>>& GetChildren();

        void SetLocalPosition(const glm::vec3& position);
        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::quat& rotation);
        void SetEuler(const glm::vec3& euler);
        void SetScale(const glm::vec3& scale);
        bool IsChild(const Transform* parent, const std::shared_ptr<Transform>& child);
        void SetParent(std::shared_ptr<Transform> parent, bool maintainWorldPosition);

        std::shared_ptr<Transform> GetParent();
    };
}