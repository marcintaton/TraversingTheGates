#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../engine/GameEngine.h"

struct DoorData : public ECS::Component::Component<DoorData> {

    bool closed = false;
    bool locked = false;
    int sturdiness = 0;
    glm::vec2 open_textue_index;
    glm::vec2 closed_texture_index;

    DoorData(bool _closed, bool _locked, int _sturdiness, glm::vec2 _open_t,
             glm::vec2 _closed_t)
    {
        closed = _closed;
        locked = _locked;
        sturdiness = _sturdiness;
        open_textue_index = _open_t;
        closed_texture_index = _closed_t;
    }
};
