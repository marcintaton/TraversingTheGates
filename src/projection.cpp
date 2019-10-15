#include "projection.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Projection::matrix(1);

void Projection::update_matrix(GLuint screen_w, GLuint screen_h,
                               GLfloat camera_zoom)
{
    Projection::matrix = glm::ortho(
        (GLfloat) screen_w * 0.5f * (1 - camera_zoom),
        (GLfloat) screen_w * 0.5f * (1 + camera_zoom),
        (GLfloat) screen_h * 0.5f * (1 - camera_zoom),
        (GLfloat) screen_h * 0.5f * (1 + camera_zoom), 0.1f, 1000.0f);
}