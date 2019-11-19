#pragma once

#include "../engine/GameEngine.h"
#include <vector>

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
    bool is_reserved;
};

struct KeyRelease : public Event::Event<KeyRelease> {
    int key_code;
};

struct SetKeysReservation : public Event::Event<SetKeysReservation> {
    std::vector<int> key_codes;
    bool to_state;
};

struct Kick : public Event::Event<Kick> {
    ECS::EntityId source;
    ECS::EntityId target;
};

struct Use : public Event::Event<Use> {
    ECS::EntityId source;
    ECS::EntityId target;
};