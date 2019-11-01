#include "camera.h"
#include "glm/glm.hpp"
#include "timer.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) :
    speed(SPEED), zoom(ZOOM), front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)), right(glm::vec3(1.0f, 0.0f, 0.0f))
{
    this->position = position;
    this->speed = speed;
    this->zoom = zoom;

    this->max_zoom = 0.05f;
    this->min_zoom = 0.005f;
    this->zoom_step = 0.005f;
}

Camera::~Camera() {}

void Camera::process_keyboard(CameraMovement direction)
{
    GLfloat velocity = speed * Timer::delta_time;

    if (direction == CameraMovement::UP) {
        position += up * velocity;
    }
    if (direction == CameraMovement::DOWN) {
        position += -up * velocity;
    }
    if (direction == CameraMovement::LEFT) {
        position += -right * velocity;
    }
    if (direction == CameraMovement::RIGHT) {
        position += right * velocity;
    }
}

void Camera::process_mouse_scroll(GLfloat y_offset)
{
    if (zoom >= min_zoom && zoom <= max_zoom) {
        zoom += y_offset * zoom_step;
    }

    if (zoom < min_zoom) {
        zoom = min_zoom;
    } else if (zoom > max_zoom) {
        zoom = max_zoom;
    }
}

GLfloat Camera::get_zoom()
{
    return zoom;
}

glm::vec3 Camera::get_position()
{
    return position;
}

glm::vec3 Camera::get_right()
{
    return right;
}

glm::vec3 Camera::get_front()
{
    return front;
}

glm::vec3 Camera::get_up()
{
    return up;
}
