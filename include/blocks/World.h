//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef WORLD_H
#define WORLD_H
#include <ranges>
#include <unordered_map>
#include <__ranges/views.h>

#include "Chunk.h"

struct ChunkIDHash {
    std::size_t operator()(const ChunkID& id) const {
        return (std::hash<int>{}(id.first) ^ std::hash<int>{}(id.second)) << 1;
    }
};

class World {
public:
    void addChunk(std::unique_ptr<Chunk> chunk) {
        if (chunks.contains(chunk->id)) return;
        chunks.emplace(chunk->id, std::move(chunk));
    }

    bool addBlock(const glm::vec3& position) {
        ChunkID id = {position.x / Chunk::CHUNK_SIZE, position.y / Chunk::CHUNK_SIZE};
        if (!chunks.contains(id)) {
            chunks.emplace(id, std::make_unique<Chunk>(id));
        }
        return chunks.at(id)->addBlock(position);
    }

    bool removeBlock(const glm::vec3& position) const {
        const ChunkID id = {position.x / Chunk::CHUNK_SIZE, position.y / Chunk::CHUNK_SIZE};
        if (!chunks.contains(id)) return false;
        return chunks.at(id)->removeBlock(position);
    }

    [[nodiscard]] std::optional<Chunk*> getChunk(const glm::vec3& position) const {
        const ChunkID id = {position.x / Chunk::CHUNK_SIZE, position.y / Chunk::CHUNK_SIZE};
        if (!chunks.contains(id)) return {};
        return chunks.at(id).get();
    }

    auto begin() {
        return (chunks | std::views::values).begin();
    }

    auto end() {
        return (chunks | std::views::values).end();
    }

    void cleanup() {
        chunks.clear();
    }

private:
    std::unordered_map<ChunkID, std::unique_ptr<Chunk>, ChunkIDHash> chunks;
};



#endif //WORLD_H
