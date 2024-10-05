#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

#include "model.hpp"

void
init_glfw()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
}

void
init_glad()
{
    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

GLFWwindow*
create_window()
{
    init_glfw();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;

        return nullptr;
    }

    glfwMakeContextCurrent(window);

    init_glad();

    return window;
}

void
handle_events(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int
main()
{
    auto window = create_window();

    Model model{"res/models/dancing_vampire.dae"};

    // while (!glfwWindowShouldClose(window)) {
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     handle_events(window);

    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    glfwDestroyWindow(window);

    return 0;
}
