#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../engine/GameEngine.h"

struct Transform : ECS::Component::Component<Transform> {
    glm::vec3 position;
    glm::vec2 scale;
    GLfloat rotation;

    glm::vec3 up();
    glm::vec3 forward();
    glm::vec3 right();

    Transform()
    {
        position = glm::vec3(0, 0, 0);
        scale = glm::vec2(0, 0);
        rotation = 0.0f;
    }

    Transform(glm::vec3 pos, glm::vec2 scl, GLfloat rot)
    {
        position = pos;
        scale = scl;
        rotation = rot;
    }
};
