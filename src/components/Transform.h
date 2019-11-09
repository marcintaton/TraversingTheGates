#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec2 scale;
    GLfloat rotation;
};
