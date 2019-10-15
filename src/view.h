#pragma once

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

class View
{
  public:
    static glm::mat4 matrix;

  public:
    void update_matrix(GLuint window_w, GLuint window_h, glm::vec3 cam_position,
                       glm::vec3 cam_front, glm::vec3 cam_up);
};
