#pragma once

#include "Generation.h"

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../global/GlobalData.h"
#include "LevelData.h"

struct Navmesh {

    NavmeshStructure level;

    inline bool is_available(int i, int j)
    {
        for (auto e : level[i][j]) {
            if (e == false) {
                return false;
            }
        }
        return true;
    }

    void create_navmesh(LevelData data);
};
