#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/camera.h"
#include "src/gameObject.h"
#include "src/material.h"
#include "src/projection.h"
#include "src/quad.h"
#include "src/shader.h"
#include "src/timer.h"
#include "src/transform.h"
#include "src/view.h"

const auto window_w = 1200;
const auto window_h = 900;
int screen_w, screen_h;
int keys[1024];

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
Timer timer;

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

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

static void mouse_scroll_callback(GLFWwindow* window, double x_offset,
                                  double y_offsset)
{
    camera.process_mouse_scroll(-y_offsset);
}

static void move_camera()
{

    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
        camera.process_keyboard(CameraMovement::UP);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
        camera.process_keyboard(CameraMovement::DOWN);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
        camera.process_keyboard(CameraMovement::RIGHT);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
        camera.process_keyboard(CameraMovement::LEFT);
    }
}

static void load_texture(const char* file_path, GLuint& texture)
{
    int tex_width, tex_height;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto image =
        SOIL_load_image(file_path, &tex_width, &tex_height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
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

    glfwGetFramebufferSize(window, &screen_w, &screen_h);

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screen_w, screen_h);

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
        0.5f * 100, 0.5f * 100, 0.0f * 100, // position
        1.0f, 1.0f,                         // uv
        // bottom right
        0.5f * 100, -0.5f * 100, 0.0f * 100, // position
        1.0f, 0.0f,                          // uv
        // bottom left
        -0.5f * 100, -0.5f * 100, 0.0f * 100, // position
        0.0f, 0.0f,                           // uv
        // top left
        -0.5f * 100, 0.5f * 100, 0.0f * 100, // position
        0.0f,
        1.0f, // uv
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    // texture cooridinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // textue loading
    GLuint textures[3];
    load_texture("assets/textures/image1.png", textures[0]);
    load_texture("assets/textures/image2.png", textures[1]);
    load_texture("assets/textures/image3.png", textures[2]);

    View view;
    Projection projection;

    // creating objects
    GameObject gameObjects[3];

    gameObjects[0] = GameObject(
        Transform {.position = glm::vec3(0, 0, 0),
                   .rotation = 0,
                   .scale = glm::vec2(1, 1)},
        Material {.texture = textures[0], .shader = core_shader}, Quad {});

    gameObjects[1] = GameObject(
        Transform {.position = glm::vec3(0, 1, 0),
                   .rotation = 0,
                   .scale = glm::vec2(1, 1)},
        Material {.texture = textures[1], .shader = inverse_color_shader},
        Quad {});

    gameObjects[2] = GameObject(
        Transform {.position = glm::vec3(1, 0, 0),
                   .rotation = 0,
                   .scale = glm::vec2(1, 1)},
        Material {.texture = textures[2], .shader = core_shader}, Quad {});

    // game loop
    while (!glfwWindowShouldClose(window)) {

        move_camera();

        glClear(GL_COLOR_BUFFER_BIT);

        view.update_matrix(window_w, window_h, camera.get_position(),
                           camera.get_front(), camera.get_up());

        projection.update_matrix(screen_w, screen_h, camera.get_zoom());

        // draw triangles
        glBindVertexArray(VAO);

        for (auto object : gameObjects) {
            object.render();
        }

        // clear vert array
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // update deltatime
        timer.update_timer();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}