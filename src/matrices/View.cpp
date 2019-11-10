#include "View.h"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 View::matrix(1);

void View::update_matrix(GLuint window_w, GLuint window_h,
                         glm::vec3 cam_position, glm::vec3 cam_front,
                         glm::vec3 cam_up)
{
    glm::mat4 matrix(1);
    matrix =
        glm::translate(matrix, glm::vec3(window_w / 2, window_h / 2, -100.0f));
    matrix *= glm::lookAt(cam_position, cam_position + cam_front, cam_up);
    View::matrix = matrix;
}