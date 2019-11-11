#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class Wall : public ECS::Entity::Entity<Wall>
{
  public:
    Wall() {}
    Wall(glm::vec3 _position, Shader _shader, GLuint _texture);
};