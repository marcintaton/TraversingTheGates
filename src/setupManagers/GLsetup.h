#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../global/GlobalGLData.h"

namespace Setup
{

void GL_setup()
{

    // GLFW init
    auto glfw_init_result = glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    // window
    Global::GlobalGLData::get_instance().window = glfwCreateWindow(
        Global::GlobalGLData::get_instance().window_w,
        Global::GlobalGLData::get_instance().window_h, "Sample", NULL, NULL);
    if (Global::GlobalGLData::get_instance().window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwGetFramebufferSize(Global::GlobalGLData::get_instance().window,
                           &Global::GlobalGLData::get_instance().screen_w,
                           &Global::GlobalGLData::get_instance().screen_h);

    glfwMakeContextCurrent(Global::GlobalGLData::get_instance().window);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, Global::GlobalGLData::get_instance().screen_w,
               Global::GlobalGLData::get_instance().screen_h);
    glEnable(GL_DEPTH_TEST);

    // textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GL_cleanup()
{
    glfwTerminate();
}

}; // namespace Setup