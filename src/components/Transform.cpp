#include "Transform.h"

glm::vec3 Transform::up()
{
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Transform::forward()
{
    return glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Transform::right()
{
    return glm::vec3(1.0f, 0.0f, 0.0f);
}