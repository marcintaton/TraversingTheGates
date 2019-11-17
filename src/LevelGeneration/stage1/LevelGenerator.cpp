#include "LevelGenerator.h"

LevelBlueprint LevelGenerator::generate_blueprint()
{
    auto blueprint = LevelBlueprint();

    blueprint.base_level = {{
        {{2, 2, 2, 2, 2, 2, 2, 2, 0, 0}},
        {{2, 1, 1, 1, 1, 1, 1, 2, 0, 0}},
        {{2, 1, 1, 1, 1, 1, 1, 2, 2, 2}},
        {{2, 1, 1, 1, 1, 1, 1, 1, 1, 2}},
        {{2, 2, 2, 1, 1, 1, 1, 1, 1, 2}},
        {{2, 1, 1, 1, 1, 1, 1, 1, 1, 2}},
        {{2, 2, 1, 1, 1, 1, 1, 1, 1, 2}},
        {{0, 2, 1, 1, 1, 1, 1, 1, 1, 2}},
        {{0, 2, 1, 1, 1, 1, 1, 1, 2, 2}},
        {{0, 2, 2, 2, 2, 2, 2, 2, 2, 2}},
    }};

    blueprint.top_level = {{{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}}};

    return blueprint;
}

LevelBlueprint LevelGenerator::generate_full_sample_blueprint()
{
    auto blueprint = LevelBlueprint();

    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {

            if (i == 0 || j == 0 || i == 99 || j == 99) {
                blueprint.base_level[i][j] = 2;
            } else {
                blueprint.base_level[i][j] = 1;
            }
        }
    }

    blueprint.top_level[5][5] = 3;

    return blueprint;
}
