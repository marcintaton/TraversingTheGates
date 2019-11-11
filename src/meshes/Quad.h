#pragma once

#include "Mesh.h"
#include <GLFW/glfw3.h>

struct Quad : Mesh {

    Quad()
    {
        vertices = {
            // top right
            0.5f, 0.5f, 0.0f, // position
            1.0f, 1.0f,       // uv
            // bottom right
            0.5f, -0.5f, 0.0f, // position
            1.0f, 0.0f,        // uv
            // bottom left
            -0.5f, -0.5f, 0.0f, // position
            0.0f, 0.0f,         // uv
            // top left
            -0.5f, 0.5f, 0.0f, // position
            0.0f, 1.0f,        // uv
        };

        indices = {
            0, 1, 3, // first tris
            1, 2, 3  // second tris
        };
    }
};
