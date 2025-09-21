//
// Created by Agamjeet Singh on 21/09/25.
//

#ifndef BLOCKID_H
#define BLOCKID_H
#include <utility>


enum class BlockID {
    GRASS_BLOCK,
    DIRT,
};

inline std::pair<size_t, size_t> idToCoords(BlockID id) {
    switch (id) {
        case BlockID::GRASS_BLOCK: return {5, 3};
        case BlockID::DIRT: return {8, 4};
        default: return {5, 15};
    }
}

#endif //BLOCKID_H
