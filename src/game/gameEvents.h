#pragma once

#include "../events/Event.h"

class GameEvent1 : public Event::Event<GameEvent1>
{
  public:
    int x = 0;
    int y = 1;
};

class GameEvent2 : public Event::Event<GameEvent2>
{
  public:
    bool a = 0;
    float b = 1;
};