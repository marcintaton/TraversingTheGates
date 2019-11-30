#pragma once

#include "../LevelGeneration/MapPosition.h"
#include "../engine/GameEngine.h"

class NavigationData : public ECS::Component::Component<NavigationData>
{
  public:
    bool passable;
    MapPosition current_position;

    NavigationData()
    {
        passable = true;
        current_position.i = -1;
        current_position.j = -1;
    }
    NavigationData(bool _passable, int pos_x, int pos_y)
    {
        passable = _passable;
        current_position.i = pos_x;
        current_position.j = pos_y;
    }
};
