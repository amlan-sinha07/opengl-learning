#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

struct MeshVertex {
    glm::vec3 Position{0.0F, 0.0F, 0.0F};
    glm::vec3 Color{0.0F, 0.0F, 0.0F};
    glm::vec3 Normal{0.0F, 0.0F, 0.0F};
    /*
    glm::vec2 UV; // texture coordinates
    glm::uvec4 BoneIDs;
    glm::vec4 BoneWeights
    */
};

/*
struct Bone{
    std::string Name;
    glm::mat4 Offset;
    glm::mat4 Transform;
};
*/

/* struct Vertex {
    glm::vec3 position;
    glm::vec3 color;

    Vertex() = default;

    Vertex(
        const glm::vec3& pos,
        const glm::vec3& col
    )
        : position{pos},
          color{col}
    {
    }
}; */
