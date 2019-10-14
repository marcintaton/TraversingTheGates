#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/camera.h"
#include "src/shader.h"
#include "src/timer.h"

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

static void set_camera_size(float ortho_size, glm::mat4& projection_matrix)
{
    projection_matrix =
        glm::ortho((GLfloat) screen_w * 0.5f * (1 - ortho_size),
                   (GLfloat) screen_w * 0.5f * (1 + ortho_size),
                   (GLfloat) screen_h * 0.5f * (1 - ortho_size),
                   (GLfloat) screen_h * 0.5f * (1 + ortho_size), 0.1f, 1000.0f);
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

    // std::cout << camera.get_position().x << " " << camera.get_position().y
    //           << " " << camera.get_position().z << std::endl;
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
        0.5f * 500, 0.5f * 500, 0.0f * 500, // position
        1.0f, 1.0f,                         // uv
        // bottom right
        0.5f * 500, -0.5f * 500, 0.0f * 500, // position
        1.0f, 0.0f,                          // uv
        // bottom left
        -0.5f * 500, -0.5f * 500, 0.0f * 500, // position
        0.0f, 0.0f,                           // uv
        // top left
        -0.5f * 500, 0.5f * 500, 0.0f * 500, // position
        0.0f,
        1.0f, // uv
    };

    GLuint indices[] = {
        0, 1, 3, // first tris
        1, 2, 3  // second tris
    };

    glm::vec3 quad_positions[] = {glm::vec3(0.0f, 0.0f, 0.0f),
                                  glm::vec3(500.1f, 0.0f, 0.0f),
                                  glm::vec3(0.0f, 500.1f, 0.0f)};

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
    // int tex_width, tex_height;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // auto image = SOIL_load_image("assets/textures/image1.png", &tex_width,
    //                              &tex_height, 0, SOIL_LOAD_RGBA);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0,
    // GL_RGBA,
    //              GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);

    // SOIL_free_image_data(image);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // game loop
    while (!glfwWindowShouldClose(window)) {

        move_camera();

        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection(1);
        set_camera_size(camera.get_zoom(), projection);

        // use shader program

        glm::mat4 view(1);

        view = camera.get_view_matrix(window_w, window_h);

        // draw triangles
        glBindVertexArray(VAO);

        for (GLuint i = 0; i < 3; ++i) {

            Shader to_use = (i == 1) ? inverse_color_shader : core_shader;
            to_use.use();

            // pass matrices to shader
            GLint model_location =
                glGetUniformLocation(to_use.program, "model");
            GLint view_location = glGetUniformLocation(to_use.program, "view");
            GLint proj_location =
                glGetUniformLocation(to_use.program, "projection");

            // bind texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glUniform1i(glGetUniformLocation(to_use.program, "texture1"), 0);

            glm::mat4 quad_model(1);
            quad_model = glm::translate(quad_model, quad_positions[i]);

            glUniformMatrix4fv(model_location, 1, GL_FALSE,
                               glm::value_ptr(quad_model));
            glUniformMatrix4fv(view_location, 1, GL_FALSE,
                               glm::value_ptr(view));
            glUniformMatrix4fv(proj_location, 1, GL_FALSE,
                               glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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