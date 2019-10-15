#pragma once

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

class Projection
{
  public:
    static glm::mat4 matrix;

  public:
    void update_matrix(GLuint screen_w, GLuint screen_h, GLfloat camera_zoom);
};
