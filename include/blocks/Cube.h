//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glm/glm.hpp>

class Cube {
public:
    explicit Cube(glm::vec3 center, float radius = 0.5f): center(center), radius(radius) {
        vertices = {
            center.x - radius, center.y - radius, center.z - radius,
            center.x - radius, center.y - radius, center.z + radius,
            center.x - radius, center.y + radius, center.z - radius,
            center.x - radius, center.y + radius, center.z + radius,
            center.x + radius, center.y - radius, center.z - radius,
            center.x + radius, center.y - radius, center.z + radius,
            center.x + radius, center.y + radius, center.z - radius,
            center.x + radius, center.y + radius, center.z + radius
        };

        faces = {
            // Front face (z+)
            center.x - radius, center.y - radius, center.z + radius, 0.0f, 0.0f,
            center.x + radius, center.y - radius, center.z + radius, 1.0f, 0.0f,
            center.x + radius, center.y + radius, center.z + radius, 1.0f, 1.0f,
            center.x + radius, center.y + radius, center.z + radius, 1.0f, 1.0f,
            center.x - radius, center.y + radius, center.z + radius, 0.0f, 1.0f,
            center.x - radius, center.y - radius, center.z + radius, 0.0f, 0.0f,

            // Back face (z-)
            center.x + radius, center.y - radius, center.z - radius, 0.0f, 0.0f,
            center.x - radius, center.y - radius, center.z - radius, 1.0f, 0.0f,
            center.x - radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x - radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x + radius, center.y + radius, center.z - radius, 0.0f, 1.0f,
            center.x + radius, center.y - radius, center.z - radius, 0.0f, 0.0f,

            // Left face (x-)
            center.x - radius, center.y - radius, center.z - radius, 0.0f, 0.0f,
            center.x - radius, center.y - radius, center.z + radius, 1.0f, 0.0f,
            center.x - radius, center.y + radius, center.z + radius, 1.0f, 1.0f,
            center.x - radius, center.y + radius, center.z + radius, 1.0f, 1.0f,
            center.x - radius, center.y + radius, center.z - radius, 0.0f, 1.0f,
            center.x - radius, center.y - radius, center.z - radius, 0.0f, 0.0f,

            // Right face (x+)
            center.x + radius, center.y - radius, center.z + radius, 0.0f, 0.0f,
            center.x + radius, center.y - radius, center.z - radius, 1.0f, 0.0f,
            center.x + radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x + radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x + radius, center.y + radius, center.z + radius, 0.0f, 1.0f,
            center.x + radius, center.y - radius, center.z + radius, 0.0f, 0.0f,

            // Bottom face (y-)
            center.x - radius, center.y - radius, center.z - radius, 0.0f, 1.0f,
            center.x + radius, center.y - radius, center.z - radius, 1.0f, 1.0f,
            center.x + radius, center.y - radius, center.z + radius, 1.0f, 0.0f,
            center.x + radius, center.y - radius, center.z + radius, 1.0f, 0.0f,
            center.x - radius, center.y - radius, center.z + radius, 0.0f, 0.0f,
            center.x - radius, center.y - radius, center.z - radius, 0.0f, 1.0f,

            // Top face (y+)
            center.x - radius, center.y + radius, center.z + radius, 0.0f, 0.0f,
            center.x + radius, center.y + radius, center.z + radius, 1.0f, 0.0f,
            center.x + radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x + radius, center.y + radius, center.z - radius, 1.0f, 1.0f,
            center.x - radius, center.y + radius, center.z - radius, 0.0f, 1.0f,
            center.x - radius, center.y + radius, center.z + radius, 0.0f, 0.0f
        };
    }

    [[nodiscard]] const std::vector<float>& getVertices() const {
        return vertices;
    }

    [[nodiscard]] const std::vector<float>& getFaces() const {
        return faces;
    }

    [[nodiscard]] glm::vec3 getPosition() const {
        return center;
    }

private:
    glm::vec3 center;
    float radius;
    std::vector<float> vertices;
    std::vector<float> faces;
};



#endif //CUBE_H
