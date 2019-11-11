#pragma once

#include "LevelBlueprint.h"
#include "LevelData.h"

// For now here

class DungeonLevelGenerator
{
  private:
    template<int W, int H>
    LevelBlueprint<W, H> generate_blueprint()
    {
        auto blueprint = LevelBlueprint<W, H>();
        //

        return blueprint;
    }

  public:
    template<int W, int H>
    LevelData<W, H> get_generated_level()
    {
        auto blueprint = generate_blueprint<W, H>();
        auto data = LevelData<W, H>();

        return data;
    }
};