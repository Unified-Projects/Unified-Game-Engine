#include <Unified-Engine/Objects/Components/collider.h>

using namespace UnifiedEngine;

// Check if a point is inside a triangle using barycentric coordinates
bool isPointInTriangle(const glm::vec3& point, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, bool ccw)
{
    glm::vec3 u = v1 - v0;
    glm::vec3 v = v2 - v0;
    glm::vec3 w = point - v0;

    float uu = glm::dot(u, u);
    float uv = glm::dot(u, v);
    float vv = glm::dot(v, v);
    float wu = glm::dot(w, u);
    float wv = glm::dot(w, v);

    float denom = uv * uv - uu * vv;
    if (fabs(denom) < 1e-6f)
        return false; // Degenerate triangle

    float s = (uv * wv - vv * wu) / denom;
    float t = (uv * wu - uu * wv) / denom;

    if (ccw)
        return (s >= 0.0f && t >= 0.0f && s + t <= 1.0f); // CCW
    else
        return (s <= 0.0f && t <= 0.0f && s + t >= -1.0f); // CW
}

// Möller-Trumbore algorithm for triangle-triangle intersection
bool triangleIntersects(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
                        const glm::vec3& u0, const glm::vec3& u1, const glm::vec3& u2, bool ccw = true)
{
    // Edge vectors for triangle v (v0, v1, v2)
    glm::vec3 vEdge1 = v1 - v0;
    glm::vec3 vEdge2 = v2 - v0;

    // Edge vectors for triangle u (u0, u1, u2)
    glm::vec3 uEdge1 = u1 - u0;
    glm::vec3 uEdge2 = u2 - u0;

    // Triangle normal direction (to check for orientation)
    glm::vec3 normalV = glm::normalize(glm::cross(vEdge1, vEdge2));
    glm::vec3 normalU = glm::normalize(glm::cross(uEdge1, uEdge2));

    // Orientation check
    if (ccw)
    {
        if (glm::dot(normalV, normalU) < 0) // Opposite direction
            return false;
    }
    else
    {
        if (glm::dot(normalV, normalU) > 0) // Same direction
            return false;
    }

    // Check if any vertex of u is inside v
    if (isPointInTriangle(u0, v0, v1, v2, ccw) ||
        isPointInTriangle(u1, v0, v1, v2, ccw) ||
        isPointInTriangle(u2, v0, v1, v2, ccw))
    {
        return true;
    }

    // Check if any vertex of v is inside u
    if (isPointInTriangle(v0, u0, u1, u2, ccw) ||
        isPointInTriangle(v1, u0, u1, u2, ccw) ||
        isPointInTriangle(v2, u0, u1, u2, ccw))
    {
        return true;
    }

    // Check edge-edge intersections
    auto edgeIntersect = [](const glm::vec3& p1, const glm::vec3& p2,
                            const glm::vec3& q1, const glm::vec3& q2) -> bool {
        glm::vec3 r = p2 - p1;
        glm::vec3 s = q2 - q1;
        glm::vec3 qp = q1 - p1;

        float rsCross = glm::length(glm::cross(r, s));
        if (fabs(rsCross) < 1e-6f) // Parallel or collinear
            return false;

        float t = glm::dot(glm::cross(qp, s), glm::cross(r, s)) / rsCross;
        float u = glm::dot(glm::cross(qp, r), glm::cross(r, s)) / rsCross;

        return (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f);
    };

    // Check all edges of both triangles
    glm::vec3 edgesV[3][2] = {{v0, v1}, {v1, v2}, {v2, v0}};
    glm::vec3 edgesU[3][2] = {{u0, u1}, {u1, u2}, {u2, u0}};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (edgeIntersect(edgesV[i][0], edgesV[i][1], edgesU[j][0], edgesU[j][1]))
            {
                return true;
            }
        }
    }

    // No intersection found
    return false;
}

// bool MeshCollider::intersects(MeshCollider* Other){

//     if(!this->mesh->GeneratedAABB){
//         this->mesh->GeneratedAABB = computeAABB(this->mesh);
//     }
//     if(!Other->mesh->GeneratedAABB){
//         Other->mesh->GeneratedAABB = computeAABB(Other->mesh);
//     }

//     // Compute AABBs
//     AABB* box1 = this->mesh->GeneratedAABB;
//     AABB* box2 = Other->mesh->GeneratedAABB;

//     // Quick rejection using AABB
//     if (!box1->intersects(box2))
//     {
//         return false;
//     }

//     // Detailed triangle-triangle checks
//     for (size_t i = 0; i < this->mesh->indices.size(); i += 3)
//     {
//         glm::vec3 v0 = this->mesh->vertices[this->mesh->indices[i]].position + this->Offset;
//         glm::vec3 v1 = this->mesh->vertices[this->mesh->indices[i + 1]].position + this->Offset;
//         glm::vec3 v2 = this->mesh->vertices[this->mesh->indices[i + 2]].position + this->Offset;

//         for (size_t j = 0; j < Other->mesh->indices.size(); j += 3)
//         {
//             glm::vec3 u0 = Other->mesh->vertices[Other->mesh->indices[j]].position + Other->Offset;
//             glm::vec3 u1 = Other->mesh->vertices[Other->mesh->indices[j + 1]].position + Other->Offset;
//             glm::vec3 u2 = Other->mesh->vertices[Other->mesh->indices[j + 2]].position + Other->Offset;

//             if (triangleIntersects(v0, v1, v2, u0, u1, u2))
//             {
//                 return true; // Collision detected
//             }
//         }
//     }

//     return false; // No collision
// }