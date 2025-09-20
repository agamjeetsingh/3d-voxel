//
// Created by Agamjeet Singh on 20/09/25.
//

#include "Camera.h"

glm::mat4 Camera::getMVP() const {
    return projection * glm::lookAt(camera_pos, looking_at, up_vector) * model;
}

void Camera::update(float deltaTime) {
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::W)) {
        camera_pos += normalize(looking_at - camera_pos) * SPEED * deltaTime;
    }
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::S)) {
        camera_pos += normalize(looking_at - camera_pos) * -SPEED * deltaTime;
    }
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::A)) {
        camera_pos += normalize(glm::cross(looking_at - camera_pos, up_vector)) * SPEED * deltaTime;
        looking_at += normalize(glm::cross(looking_at - camera_pos, up_vector)) * -SPEED * deltaTime;
    }
    if (InputManager::getInstance().isPressed(sf::Keyboard::Key::D)) {
        camera_pos += normalize(glm::cross(looking_at - camera_pos, up_vector)) * -SPEED * deltaTime;
        looking_at += normalize(glm::cross(looking_at - camera_pos, up_vector)) * SPEED * deltaTime;
    }
}

