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
        include/utility/InputManagerWrapper.cpp
        include/utility/InputManagerWrapper.h
        include/Camera.cpp
        include/Camera.h)

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

