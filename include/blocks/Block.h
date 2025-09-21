//
// Created by Agamjeet Singh on 21/09/25.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "BlockID.h"
#include "Cube.h"
#include "../rendering/TextureAtlas.h"


class Block: public Cube {
public:
    explicit Block(const glm::vec3 position, const BlockID id): Cube(position) {
        const auto tile_coords = idToCoords(id);
        const auto [bottom_left, bottom_right, top_right, top_left] = TextureAtlas::getUVs(tile_coords);
        faces = {
            // Front face (z+)
            center.x - radius, center.y - radius, center.z + radius, bottom_left.u, bottom_left.v,
            center.x + radius, center.y - radius, center.z + radius, bottom_right.u, bottom_right.v,
            center.x + radius, center.y + radius, center.z + radius, top_right.u, top_right.v,
            center.x + radius, center.y + radius, center.z + radius, top_right.u, top_right.v,
            center.x - radius, center.y + radius, center.z + radius, top_left.u, top_left.v,
            center.x - radius, center.y - radius, center.z + radius, bottom_left.u, bottom_left.v,

            // Back face (z-)
            center.x + radius, center.y - radius, center.z - radius, bottom_left.u, bottom_left.v,
            center.x - radius, center.y - radius, center.z - radius, bottom_right.u, bottom_right.v,
            center.x - radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x - radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x + radius, center.y + radius, center.z - radius, top_left.u, top_left.v,
            center.x + radius, center.y - radius, center.z - radius, bottom_left.u, bottom_left.v,

            // Left face (x-)
            center.x - radius, center.y - radius, center.z - radius, bottom_left.u, bottom_left.v,
            center.x - radius, center.y - radius, center.z + radius, bottom_right.u, bottom_right.v,
            center.x - radius, center.y + radius, center.z + radius, top_right.u, top_right.v,
            center.x - radius, center.y + radius, center.z + radius, top_right.u, top_right.v,
            center.x - radius, center.y + radius, center.z - radius, top_left.u, top_left.v,
            center.x - radius, center.y - radius, center.z - radius, bottom_left.u, bottom_left.v,

            // Right face (x+)
            center.x + radius, center.y - radius, center.z + radius, bottom_left.u, bottom_left.v,
            center.x + radius, center.y - radius, center.z - radius, bottom_right.u, bottom_right.v,
            center.x + radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x + radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x + radius, center.y + radius, center.z + radius, top_left.u, top_left.v,
            center.x + radius, center.y - radius, center.z + radius, bottom_left.u, bottom_left.v,

            // Bottom face (y-)
            center.x - radius, center.y - radius, center.z - radius, top_left.u, top_left.v,
            center.x + radius, center.y - radius, center.z - radius, top_right.u, top_right.v,
            center.x + radius, center.y - radius, center.z + radius, bottom_right.u, bottom_right.v,
            center.x + radius, center.y - radius, center.z + radius, bottom_right.u, bottom_right.v,
            center.x - radius, center.y - radius, center.z + radius, bottom_left.u, bottom_left.v,
            center.x - radius, center.y - radius, center.z - radius, top_left.u, top_left.v,

            // Top face (y+)
            center.x - radius, center.y + radius, center.z + radius, bottom_left.u, bottom_left.v,
            center.x + radius, center.y + radius, center.z + radius, bottom_right.u, bottom_right.v,
            center.x + radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x + radius, center.y + radius, center.z - radius, top_right.u, top_right.v,
            center.x - radius, center.y + radius, center.z - radius, top_left.u, top_left.v,
            center.x - radius, center.y + radius, center.z + radius, bottom_left.u, bottom_left.v
        };
    }

    [[nodiscard]] const std::vector<float>& getFaces() const {
        return faces;
    }
private:
    std::vector<float> faces;
};



#endif //BLOCK_H
