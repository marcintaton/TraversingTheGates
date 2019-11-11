#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Projection
{
  public:
    static glm::mat4 matrix;

    void update_matrix(GLuint screen_w, GLuint screen_h, GLfloat camera_zoom);
};
