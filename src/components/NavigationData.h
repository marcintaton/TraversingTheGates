#pragma once

#include "../engine/GameEngine.h"

class NavigationData : public ECS::Component::Component<NavigationData>
{
  public:
    bool passable;

    NavigationData() {}
    NavigationData(bool _passable) { passable = _passable; }
};
