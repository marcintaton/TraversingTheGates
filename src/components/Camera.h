#pragma once

#include <GL/glew.h>

struct Camera {
    const GLfloat initial_zoom = 0.05f;
    const GLfloat max_zoom = 0.05f;
    const GLfloat min_zoom = 0.005f;
    const GLfloat zoom_step = 0.005f;

    GLfloat zoom = initial_zoom;
};
