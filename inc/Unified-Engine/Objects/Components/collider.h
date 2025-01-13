#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <GLM/vec3.hpp>
#include <Unified-Engine/Objects/Mesh/mesh.h>

namespace UnifiedEngine
{
    enum ColliderType{
        COLLIDER_BOX = 1,
        COLLIDER_SPHERE,
        COLLIDER_MESH
    };

    class BoxCollider;
    class SphericalCollider;

    class Collider : public ObjectComponent{
    public: //CollisionChecks
        Collider(ObjectComponent* Parent, ColliderType CType) : ObjectComponent(Parent, OBJECT_COLLIDER, true), Type(CType){}

    public:
        glm::vec3 Offset = glm::vec3(0.0f);
    protected:
        const ColliderType Type;
    };

    class BoxCollider : public Collider{
    public:
        glm::vec3 Size = glm::vec3(0.0f);
        AABB* BoundingBox = nullptr;
    public:
        BoxCollider(ObjectComponent* Parent, AABB* BB) : Collider(Parent, COLLIDER_BOX), BoundingBox(BB) {};

        bool operator^(const UnifiedEngine::BoxCollider& other) const {
            // Perform collision detection logic here
            if (!BoundingBox || !other.BoundingBox) return false;

            const auto& aMin = BoundingBox->min + Offset;
            const auto& aMax = BoundingBox->max + Offset;
            const auto& bMin = other.BoundingBox->min + other.Offset;
            const auto& bMax = other.BoundingBox->max + other.Offset;

            return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
                (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
                (aMin.z <= bMax.z && aMax.z >= bMin.z);
        }
    };

    // class SphericalCollider : public Collider{
    // public:
    //     float Radius = 0.0f;
    // };

    // class MeshCollider : public Collider{
    // public:
    //     MeshCollider() {}

    //     Mesh* mesh = nullptr;

    //     bool intersects(MeshCollider* Other);
    // };
} // namespace UnifiedEngine
