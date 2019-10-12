#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

#include "src/shader.h"

const auto window_w = 1200;
const auto window_h = 900;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    // GLFW init
    auto glfw_init_result = glfwInit();

    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    // window
    GLFWwindow* window =
        glfwCreateWindow(window_w, window_h, "Sample", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    Shader coreShader("src/shaders/core.vs", "src/shaders/core.fs");
    Shader inverseShader("src/shaders/core.vs", "src/shaders/inverse.fs");

    // geometry
    GLfloat new_vertices[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                              // bottom left
                              0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                              // bottom tight
                              0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f}; // middle top
    GLuint VBO;
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(new_vertices), new_vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT),
                          (GLvoid*) (3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    bool shader_change = true;

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        shader_change ? coreShader.use() : inverseShader.use();
        shader_change = !shader_change;
        glBindVertexArray(VAO);
        glDrawArrays(GL_POLYGON, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}