//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef INPUTMANAGERWRAPPER_H
#define INPUTMANAGERWRAPPER_H

#include <ranges>
#include <unordered_map>
#include <GLFW/glfw3.h>

#include "utility/InputManager.h"


class InputManagerWrapper {
public:
    struct KeyData {
        int glfwKey = 0;
        int lastState = GLFW_RELEASE;
    };

    InputManagerWrapper() {
        keys[sf::Keyboard::Key::W] = {GLFW_KEY_W, GLFW_RELEASE};
        keys[sf::Keyboard::Key::A] = {GLFW_KEY_A, GLFW_RELEASE};
        keys[sf::Keyboard::Key::S] = {GLFW_KEY_S, GLFW_RELEASE};
        keys[sf::Keyboard::Key::D] = {GLFW_KEY_D, GLFW_RELEASE};
        keys[sf::Keyboard::Key::Escape] = {GLFW_KEY_ESCAPE, GLFW_RELEASE};
        keys[sf::Keyboard::Key::Space] = {GLFW_KEY_SPACE, GLFW_RELEASE};
    }

    void update(GLFWwindow* window) {
        // Iterate over keys we care about
        for (auto& [sfml_key, data] : keys) {
            int currentState = glfwGetKey(window, data.glfwKey);

            if (currentState == GLFW_PRESS && data.lastState == GLFW_RELEASE) {
                InputManager::getInstance().keyPressed(sfml_key);
            }
            if (currentState == GLFW_RELEASE && data.lastState == GLFW_PRESS) {
                InputManager::getInstance().keyReleased(sfml_key);
            }

            data.lastState = currentState;
        }
    }

private:
    std::unordered_map<sf::Keyboard::Key, KeyData> keys;
};



#endif //INPUTMANAGERWRAPPER_H
