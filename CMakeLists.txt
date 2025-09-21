cmake_minimum_required(VERSION 3.31)
project(3d_voxel)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(3d_voxel main.cpp
        vendor/stb_image.h
        vendor/stb_impl.cpp
        vendor/glad/src/glad.c
        src/utility/InputManagerWrapper.cpp
        include/utility/InputManagerWrapper.h
        src/rendering/Camera.cpp
        include/rendering/Camera.h
        src/blocks/Cube.cpp
        include/blocks/Cube.h
        include/rendering/TextureShader.cpp
        include/rendering/TextureShader.h
        include/blocks/Chunk.cpp
        include/blocks/Chunk.h
        include/blocks/World.cpp
        include/blocks/World.h
        include/rendering/TextureAtlas.cpp
        include/rendering/TextureAtlas.h
        include/blocks/Block.cpp
        include/blocks/Block.h
        include/blocks/BlockID.h)

target_include_directories(3d_voxel PRIVATE
        vendor/glad/include
        vendor/stb
)

FetchContent_Declare(
        game_lib
        GIT_REPOSITORY https://github.com/agamjeetsingh/2d-game-engine.git
        GIT_TAG v0.1.1-alpha
)
FetchContent_MakeAvailable(game_lib)

target_link_libraries(3d_voxel PRIVATE
        glfw
        glm::glm
        "-framework OpenGL"
        game_lib
)

