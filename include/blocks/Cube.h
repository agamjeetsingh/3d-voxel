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
    }

    [[nodiscard]] const std::vector<float>& getVertices() const {
        return vertices;
    }

    [[nodiscard]] glm::vec3 getPosition() const {
        return center;
    }

protected:
    const glm::vec3 center;
    const float radius;

private:
    std::vector<float> vertices;
};



#endif //CUBE_H
