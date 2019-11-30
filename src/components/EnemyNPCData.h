#pragma once

#include "../engine/GameEngine.h"

struct EnemyNPCData : public ECS::Component::Component<EnemyNPCData> {

    int vision_range = 0;
    int attack_range = 0;
    bool hostile = false;

    EnemyNPCData(int _v_range, int _a_range)
    {
        vision_range = _v_range;
        attack_range = _a_range;
    }

    EnemyNPCData(int _v_range, int _a_range, bool _hostile)
    {
        vision_range = _v_range;
        attack_range = _a_range;
        hostile = _hostile;
    }
};