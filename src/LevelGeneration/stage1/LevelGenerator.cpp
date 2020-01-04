#include "LevelGenerator.h"

LevelBlueprint LevelGenerator::generate_blueprint()
{
    auto blueprint = LevelBlueprint();

    blueprint.level = {{
        {{{2}, {2}, {2}, {2}, {2}, {2}, {2}, {2}, {2}, {2}}},
        {{{2}, {1}, {1}, {1}, {1}, {1}, {1}, {2}, {1}, {2}}},
        {{{2}, {2}, {2}, {1}, {1}, {1}, {1}, {2}, {1, 5}, {2}}},
        {{{2}, {1}, {1, 4}, {1}, {1}, {1}, {1}, {1}, {1, 6}, {2}}},
        {{{2}, {2}, {2}, {1}, {1}, {1}, {1}, {1}, {1}, {2}}},
        {{{2}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {2}}},
        {{{2}, {2}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {2}}},
        {{{0}, {2}, {1}, {1, 3}, {1}, {1}, {1}, {1}, {1}, {2}}},
        {{{0}, {2}, {1}, {1}, {1}, {1}, {1}, {1}, {2}, {2}}},
        {{{0}, {2}, {2}, {2}, {2}, {2}, {2}, {2}, {2}, {2}}},
    }};

    return blueprint;
}

LevelBlueprint LevelGenerator::generate_full_size()
{
    auto blueprint = LevelBlueprint();

    for (size_t i = 0; i < 200; ++i) {
        for (size_t j = 0; j < 200; j++) {
            if (i == 2 && j == 2) {
                blueprint.level[i][j] = {1, 3};
            } else {
                blueprint.level[i][j] = {1};
            }
        }
    }

    return blueprint;
}
