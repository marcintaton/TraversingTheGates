#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class Tile : public ECS::Entity::Entity<Tile>
{
  public:
    Tile() {}
    Tile(glm::vec3 _position, Shader _shader, GLuint _texture);
};