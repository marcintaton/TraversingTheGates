#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    GLfloat rotation;
    glm::vec2 scale;
};
