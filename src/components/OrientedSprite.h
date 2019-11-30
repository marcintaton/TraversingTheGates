#pragma once

#include <glm/glm.hpp>
#include <map>

#include "../engine/GameEngine.h"
#include "../others/Direction.h"

class OrientedSprite : public ECS::Component::Component<OrientedSprite>
{
  public:
    Direction current_direction = Direction::DOWN;
    std::map<Direction, glm::vec2> texture_sprite_coords;

    OrientedSprite() {}
    OrientedSprite(glm::vec2 up, glm::vec2 down, glm::vec2 right,
                   glm::vec2 left)
    {
        texture_sprite_coords[Direction::UP] = up;
        texture_sprite_coords[Direction::DOWN] = down;
        texture_sprite_coords[Direction::RIGHT] = right;
        texture_sprite_coords[Direction::LEFT] = left;
    }
};
