#pragma once

#include "../engine/GameEngine.h"

struct OnLoadNewLevel : public Event::Event<OnLoadNewLevel> {
};

struct OnKeyPress : public Event::Event<OnKeyPress> {
    int key_code;
};

struct OnKeyRelease : public Event::Event<OnKeyRelease> {
    int key_code;
};
