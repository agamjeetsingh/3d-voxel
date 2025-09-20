#include <stdexcept>
#include "vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "include/utility/InputManagerWrapper.h"

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft Clone", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to init GLAD");
    }

    InputManagerWrapper input_manager_wrapper;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(200, 200, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        input_manager_wrapper.update(window);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            // left click pressed
        }

    }

    glfwTerminate();
}
