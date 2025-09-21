#include <iostream>
#include <stdexcept>
#include "vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/blocks/Chunk.h"
#include "include/blocks/World.h"
#include "include/rendering/Camera.h"
#include "include/rendering/TextureShader.h"
#include "include/utility/InputManagerWrapper.h"
#include "vendor/stb_image.h"

int main() {
    // -------------------- GLFW + GLAD init --------------------
    if (!glfwInit()) throw std::runtime_error("Failed to init GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // request OpenGL 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // macOS max = 4.1
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // REQUIRED on Mac


    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle Example", nullptr, nullptr);
    if (!window) throw std::runtime_error("Failed to create GLFW window");
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // TODO - Check for success

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        throw std::runtime_error("Failed to init GLAD");

    InputManagerWrapper input_manager_wrapper;

    TextureShader texture_shader;

    World world;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                assert(world.addBlock(Block{{i, k, j}, BlockID::GRASS_BLOCK}));
            }
        }
    }

    TextureAtlas atlas;

    glUniform1i(glGetUniformLocation(texture_shader.getShaderProgram(), "texture1"), 0);

    Camera camera;

    glfwSetWindowUserPointer(window, &camera);

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
        auto cb = [cam](float xpos, float ypos){
            static bool firstMouse = true;
            static float lastX = 400, lastY = 300; // window center
            static float sensitivity = 0.1f;

            if (firstMouse) { // avoid jump when first captured
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed: y-coordinates go from bottom to top
            lastX = xpos;
            lastY = ypos;

            xoffset *= sensitivity;
            yoffset *= sensitivity;

            cam->yaw += xoffset;
            cam->pitch += yoffset;

            if (cam->pitch > 90.0f) cam->pitch = 90.0f;
            if (cam->pitch < -90.0f) cam->pitch = -90.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
            direction.y = sin(glm::radians(cam->pitch));
            direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
            cam->camera_front = glm::normalize(direction);
        };
        cb(xpos, ypos);
    });

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime(); // seconds since glfwInit
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        input_manager_wrapper.update(window);

        camera.update(deltaTime);

        // render
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.2f, 0.0f, 1.0f); // note: floats 0.0-1.0
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        unsigned int mvpLoc = glGetUniformLocation(texture_shader.getShaderProgram(), "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(camera.getMVP()));

        // ---- Camera Logic End ----

        // draw triangles
        for (const auto& ptr: world) {
            glUseProgram(texture_shader.getShaderProgram());
            glBindVertexArray(ptr->getVAO());
            std::cout << ptr->getNumVertices() << std::endl;
            glDrawArrays(GL_TRIANGLES, 0, ptr->getNumVertices());
        }

        glfwSwapBuffers(window);
    }

    // cleanup
    glDeleteProgram(texture_shader.getShaderProgram());
    world.cleanup();
    glfwTerminate();
}
