//
// Created by Agamjeet Singh on 20/09/25.
//

#include "../../include/rendering/Camera.h"

glm::mat4 Camera::getMVP() const {
    return projection * glm::lookAt(camera_pos, camera_pos + camera_front, up_vector) * model;
}

void Camera::update(float deltaTime) {
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::W)) {
        camera_pos += camera_front * SPEED * deltaTime;
    }
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::S)) {
        camera_pos -= camera_front * SPEED * deltaTime;
    }

    const glm::vec3 right = glm::normalize(glm::cross(camera_front, up_vector));

    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::D)) {
        camera_pos += right * SPEED * deltaTime;
    }
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::A)) {
        camera_pos -= right * SPEED * deltaTime;
    }
}

