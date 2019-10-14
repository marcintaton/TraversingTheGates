#pragma once

#include <GL/glew.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { UP, DOWN, LEFT, RIGHT };

const GLfloat ZOOM = 1.0f;
const GLfloat SPEED = 500.0f;

class Camera
{
  private:
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;

    glm::vec3 position;

    GLfloat speed;
    GLfloat zoom;
    GLfloat max_zoom;
    GLfloat min_zoom;
    GLfloat zoom_step;

  private:
  public:
    Camera(glm::vec3 position);
    ~Camera();

    glm::mat4 get_view_matrix(GLuint window_w, GLuint window_h);
    void process_keyboard(CameraMovement direction);
    void process_mouse_scroll(GLfloat y_offset);
    GLfloat get_zoom();
    glm::vec3 get_position();
};
