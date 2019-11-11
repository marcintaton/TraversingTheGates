#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"

class Camera : public ECS::Entity::Entity<Camera>
{

  public:
    Camera() {}
    Camera(glm::vec3 _position);
};