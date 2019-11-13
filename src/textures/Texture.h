#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Texture {
    GLuint texture_index;
    glm::vec2 atlas_offset;
    glm::vec2 atlas_size;
};
