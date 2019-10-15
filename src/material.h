#pragma once

#include "shader.h"
#include <GLFW/glfw3.h>

struct Material {

    GLuint texture;
    Shader shader;
};
