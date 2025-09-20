//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utility/InputManager.h"

class Camera {
public:
    [[nodiscard]] glm::mat4 getMVP() const;

    void update(float deltaTime);

private:
    static constexpr float SPEED = 5.0f;
    static constexpr float FOV = glm::radians(45.0f);

    glm::mat4 model = {1.0f};

    glm::vec3 camera_pos = {0.0f, 0.0f, 30.0f};

    glm::vec3 looking_at = {0.0f, 0.0f, 0.0f};

    glm::vec3 up_vector = {0.0f, 1.0f, 0.0f};

    glm::mat4 view = glm::lookAt(camera_pos, looking_at, up_vector);

    glm::mat4 projection = glm::perspective(
        FOV,          // FOV
        800.0f / 600.0f,              // aspect ratio
        0.1f, 100.0f                  // near and far clip
    );
};



#endif //CAMERA_H
