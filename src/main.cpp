#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <iostream>

#include "model.hpp"
#include "shader.hpp"

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

    Model model  {"res/models/dancing_vampire.dae"};
    Shader shader{"res/shaders/basic.vert", "res/shaders/basic.frag"};

    glm::mat4 projection = glm::perspective(
        glm::radians(45.f),
        640.f / 480.f,
        0.1f,
        100.f
    );

    glm::mat4 view = glm::lookAt(
        glm::vec3{0.f, 0.f, 3.f},
        glm::vec3{0.f, 0.f, 0.f},
        glm::vec3{0.f, 1.f, 0.f}
    );

    glm::mat4 model_matrix = glm::mat4{1.f};

    glm::mat4 mvp = projection * view * model_matrix;

    glm::mat4 model_model = glm::mat4{1.f};
    model_model = glm::translate(model_model, glm::vec3{0.f, 0.f, 2.f});

    shader.Bind();

    const auto shader_id = shader.get_id();

    const auto loc_uModel = glGetUniformLocation(shader_id, "uModel");
    const auto loc_uMVP   = glGetUniformLocation(shader_id, "uMVP");
    const auto loc_tex_diffuse = glGetUniformLocation(shader_id, "tex_diffuse");

    glUniformMatrix4fv(loc_uModel, 1, GL_FALSE, &model_model[0][0]);
    glUniformMatrix4fv(loc_uMVP, 1, GL_FALSE, &mvp[0][0]);
    glUniform1i(loc_tex_diffuse, 0);

    shader.Unbind();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        handle_events(window);

        shader.Bind();

        model.draw();
        shader.Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    return 0;
}
