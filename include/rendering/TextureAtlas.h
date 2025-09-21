//
// Created by Agamjeet Singh on 21/09/25.
//

#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include <array>
#include <utility>

#include "glad/glad.h"
#include "../../vendor/stb_image.h"

struct UV {
    float u, v;
};

class TextureAtlas {
public:
    TextureAtlas() {
        glActiveTexture(GL_TEXTURE0);
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../img.png", &width, &height, &nrChannels, 0);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // load image into texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    [[nodiscard]] static std::array<UV, 4> getUVs(std::pair<size_t, size_t> tile_coordinate) {
        auto [tileX, tileY] = tile_coordinate;
        const float u0 = static_cast<float>(tileX) * uSize;
        const float v0 = static_cast<float>(tileY) * vSize; // 1.0f - static_cast<float>(tileY + 1) * vSize;
        const float u1 = u0 + uSize;
        const float v1 = v0 + vSize; // 1.0f - static_cast<float>(tileY) * vSize;

        return {{
            {u0, v0}, // bottom-left
            {u1, v0}, // bottom-right
            {u1, v1}, // top-right
            {u0, v1}  // top-left
        }};
    }

    static constexpr size_t TILE_SIZE = 16;
    static constexpr size_t WIDTH = 512;
    static constexpr size_t HEIGHT = 256;
    static constexpr float tilesX = static_cast<float>(WIDTH) / TILE_SIZE;
    static constexpr float tilesY = static_cast<float>(HEIGHT) / TILE_SIZE;
    static constexpr float uSize = 1.0f / tilesX;  // size of one tile in U (x) direction
    static constexpr float vSize = 1.0f / tilesY;  // size of one tile in V (y) direction
};



#endif //TEXTUREATLAS_H
