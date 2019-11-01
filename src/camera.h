#pragma once

#include <GL/glew.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { UP, DOWN, LEFT, RIGHT };

const GLfloat ZOOM = 0.05f;
const GLfloat SPEED = 5.0f;

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

  public:
    Camera(glm::vec3 position);
    ~Camera();

    void process_keyboard(CameraMovement direction);
    void process_mouse_scroll(GLfloat y_offset);

    GLfloat get_zoom();
    glm::vec3 get_position();
    glm::vec3 get_right();
    glm::vec3 get_front();
    glm::vec3 get_up();
};
