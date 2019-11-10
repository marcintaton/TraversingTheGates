#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../engine/GameEngine.h"

struct Transform : ECS::Component::Component<Transform> {
    glm::vec3 position;
    glm::vec2 scale;
    GLfloat rotation;
};
