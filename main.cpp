#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
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

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    // textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // shader build
    Shader core_shader("assets/shaders/core.vs", "assets/shaders/core.fs");
    Shader inverse_color_shader("assets/shaders/core.vs",
                                "assets/shaders/inverse.fs");

    // geometry
    GLfloat quad_verices[] = {
        // top right
        0.5f, 0.5f, 0.0f, // position
        1.0f, 0.0f, 0.0f, // color
        1.0f, 1.0f,       // uv
        // bottom right
        0.5f, -0.5f, 0.0f, // position
        0.0f, 1.0f, 0.0f,  // color
        1.0f, 0.0f,        // uv
        // bottom left
        -0.5f, -0.5f, 0.0f, // position
        0.0f, 0.0f, 1.0f,   // color
        0.0f, 0.0f,         // uv
        // top left
        -0.5f, 0.5f, 0.0f, // position
        1.0f, 1.0f, 1.0f,  // color
        0.0f, 1.0f         // uv
    };

    GLuint indices[] = {
        0, 1, 3, // first tris
        1, 2, 3  // second tris
    };

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verices), quad_verices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
                          (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // texture cooridinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
                          (GLvoid*) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // textue loading
    GLuint texture;
    int tex_width, tex_height;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto image = SOIL_load_image("assets/textures/image1.png", &tex_width,
                                 &tex_height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    // game loop
    auto shader_switch = true;
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        auto shader_to_use = shader_switch ? core_shader : inverse_color_shader;
        shader_to_use.use();
        shader_switch = !shader_switch;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shader_to_use.program, "texture1"), 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}