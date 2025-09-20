//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <unordered_map>
#include <utility>
#include <vector>

#include "Cube.h"
#include "glad/glad.h"

using ChunkID = std::pair<int, int>;

struct Vec3Hash {
    std::size_t operator()(const glm::vec3& v) const noexcept {
        constexpr std::hash<float> hasher;
        return hasher(v.x) ^ (hasher(v.y) << 1) ^ (hasher(v.z) << 2);
    }
};

class Chunk {
public:
    explicit Chunk(ChunkID id): id(std::move(id)) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Bind VAO first
        glBindVertexArray(VAO);

        // Bind VBO and upload vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Tell OpenGL how to interpret vertex data
        // position: 3 floats
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coords: 2 floats
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbind for safety
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    bool addBlock(const glm::vec3& position) {
        if (vertex_map.contains(position)) return false;
        const auto block = Cube{position};
        vertices.insert(vertices.end(), block.getFaces().begin(), block.getFaces().end());
        vertex_map.emplace(block.getPosition(), vertices.size() - 1);
        updateVBO();
        return true;
    }

    bool removeBlock(const glm::vec3& position) {
        if (!vertex_map.contains(position)) {
            return false;
        }
        const size_t starting_index = vertex_map.at(position);
        const auto starting_it = vertices.begin() + static_cast<std::ptrdiff_t>(starting_index);
        const auto ending_it = vertices.begin() + static_cast<std::ptrdiff_t>(starting_index) + 180;
        vertices.erase(starting_it, ending_it);
        return true;
    }

    const ChunkID id;

    static constexpr size_t CHUNK_SIZE = 16;

    [[nodiscard]] unsigned int getVAO() const {
        return VAO;
    }

    [[nodiscard]] unsigned int getVBO() const {
        return VBO;
    }

    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;

    Chunk(Chunk&& other) noexcept {
        VAO = other.VAO;
        VBO = other.VBO;
        other.VAO = 0;
        other.VBO = 0;
    }

    Chunk& operator=(Chunk&& other) noexcept {
        if (this != &other) {
            if (glIsVertexArray(VAO)) {
                glDeleteVertexArrays(1, &VAO);
            }
            if (glIsBuffer(VBO)) {
                glDeleteBuffers(1, &VBO);
            }
            VAO = other.VAO;
            VBO = other.VBO;
            other.VAO = 0;
            other.VBO = 0;
        }
        return *this;
    }

    ~Chunk() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    [[nodiscard]] size_t getNumVertices() const {
        return vertices.size() / 5;
    }

private:
    void updateVBO() const {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /**
     * vertex_map[center] is the starting index of the 6 vertices of cube with that center.
     */
    std::unordered_map<glm::vec3, size_t, Vec3Hash> vertex_map;
    std::vector<float> vertices;

    unsigned int VAO;
    unsigned int VBO;
};



#endif //CHUNK_H
