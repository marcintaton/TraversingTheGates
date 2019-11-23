#pragma once

#include <glm/glm.hpp>
#include <map>

#include "../engine/GameEngine.h"
#include "../others/SpriteDirection.h"

class OrientedSprite : public ECS::Component::Component<OrientedSprite>
{
  public:
    SpriteDirection current_direction = SpriteDirection::DOWN;
    std::map<SpriteDirection, glm::vec2> texture_sprite_coords;

    OrientedSprite() {}
    OrientedSprite(glm::vec2 up, glm::vec2 down, glm::vec2 right,
                   glm::vec2 left)
    {
        texture_sprite_coords[SpriteDirection::UP] = up;
        texture_sprite_coords[SpriteDirection::DOWN] = down;
        texture_sprite_coords[SpriteDirection::RIGHT] = right;
        texture_sprite_coords[SpriteDirection::LEFT] = left;
    }
};
