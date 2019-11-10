#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../Globals.h"

GLFWwindow* GL_setup()
{

    // GLFW init
    auto glfw_init_result = glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    // window
    GLFWwindow* window =
        glfwCreateWindow(window_w, window_h, "Sample", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwGetFramebufferSize(window, &screen_w, &screen_h);

    glfwMakeContextCurrent(window);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screen_w, screen_h);
    glEnable(GL_DEPTH_TEST);

    // textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void GL_cleanup()
{
    glfwTerminate();
}