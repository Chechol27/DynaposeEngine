#include "Core/Transform.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace DynaPose
{
    Transform::Transform(const Transform& other)
    {
        parent = other.parent;
        localPosition = other.localPosition;
        rotation = other.rotation;
        scale = other.scale;
        children = other.children;
        UpdateMatrix();
    }

    void Transform::Update(bool dirty)
    {
        dirty |= this->dirty;
        if (dirty)
        {
            UpdateMatrix();
        }

        for (auto child: children)
        {
            if (!child) continue;
            child->Update(dirty);
        }
    }

    void Transform::UpdateMatrix()
    {
        const glm::mat4x4 rotationMat = glm::toMat4(rotation);
        localToWorld = glm::scale(glm::mat4(1.0f), scale) * rotationMat * glm::translate( glm::mat4(1.0f), localPosition);
        if (parent) localToWorld = parent->localToWorld * localToWorld;
        dirty = false;
    }

    bool Transform::GetDirty()
    {
        return dirty;
    }

    bool Transform::SetDirty(const bool& dirty)
    {
        this->dirty = dirty;
    }

    void Transform::GetLocalPosition(glm::vec3& position)
    {
        position = localPosition;
    }

    void Transform::GetPosition(glm::vec3& position)
    {
        position = !parent ?  this->localPosition : glm::vec3(glm::vec4(localPosition, 1) * parent->localToWorld);
    }

    void Transform::GetRotation(glm::quat& rotation)
    {
        rotation = this->rotation;
    }

    void Transform::GetEuler(glm::vec3& euler)
    {
        euler = glm::eulerAngles(rotation);
    }

    void Transform::GetScale(glm::vec3& scale)
    {
        scale = this->scale;
    }

    void Transform::GetLocalToWorld(glm::mat4x4& localToWorld) const
    {
        localToWorld = this->localToWorld;
    }

    void Transform::GetWorldToLocal(glm::mat4x4& worldToLocal)
    {
        worldToLocal = glm::inverse(localToWorld);
    }

    std::vector<std::shared_ptr<Transform>>& Transform::GetChildren()
    {
        return children;
    }

    void Transform::SetLocalPosition(const glm::vec3& position)
    {
        localPosition = position;
        dirty = true;
    }

    void Transform::SetPosition(const glm::vec3& position)
    {
        this->localPosition = !parent ? position : glm::vec3(glm::vec4(localPosition, 1) * parent->localToWorld);
        dirty = true;
    }

    void Transform::SetRotation(const glm::quat& rotation)
    {
        this->rotation = rotation;
        dirty = true;
    }

    void Transform::SetEuler(const glm::vec3& euler)
    {
        rotation = glm::quat(euler);
        dirty = true;
    }

    void Transform::SetScale(const glm::vec3& scale)
    {
        this->scale = scale;
        dirty = true;
    }

    bool Transform::IsChild(const Transform* parent, const std::shared_ptr<Transform>& child)
    {
        for (const auto& _child: children)
        {
            if (IsChild(parent, child))
            {
                return true;
            }
        }
        return false;
    }

    void Transform::SetParent(std::shared_ptr<Transform> parent, bool maintainWorldPosition)
    {
        bool isParentChild = parent ? IsChild(this, parent) : false;
        //Case parent is in this transform's hierarchy or parent is null
        if (parent != nullptr || isParentChild)
        {
            if (isParentChild)
                parent->SetParent(this->parent, true);
            if (maintainWorldPosition)
            {
                glm::vec3 worldPos;
                GetPosition(worldPos);
                this->parent = parent;
                SetPosition(worldPos);
            }
            else
            {
                this->parent = parent;
            }
        }
        //Case parent is null
        else
        {
            glm::vec3 worldPos;
            GetPosition(worldPos);
            SetPosition(worldPos);
            this->parent = parent;
        }
        dirty = true;
    }

    std::shared_ptr<Transform> Transform::GetParent()
    {
        return parent;
    }
}
