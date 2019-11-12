#pragma once

#include "../engine/GameEngine.h"

struct LoadNewLevel : public Event::Event<LoadNewLevel> {
};

struct TurnEnd : public Event::Event<TurnEnd> {
};

struct PlayerMoved : public Event::Event<PlayerMoved> {
    int form_x;
    int from_y;
    int to_x;
    int to_y;
};

struct KeyPress : public Event::Event<KeyPress> {
    int key_code;
};

struct KeyRelease : public Event::Event<KeyRelease> {
    int key_code;
};
