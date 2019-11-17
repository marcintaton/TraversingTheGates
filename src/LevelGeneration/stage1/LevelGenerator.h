#pragma once

#include <random>
#include <vector>

#include "../../engine/GameEngine.h"
#include "../../global/GlobalData.h"
#include "../LevelBlueprint.h"
#include "../LevelData.h"
#include "../RoomData.h"

// ????
#include "../../entities/GameEntities.h"

// For now here

class LevelGenerator
{
  private:
    int min_room_size = 5;
    int max_room_size = 8;
    int min_room_count = 15;
    int max_room_count = 15;
    int max_room_addition_tries = 10000;

    int random(int min, int max);
    //
    void try_add_room(std::vector<RoomData>& rooms, bool is_entry,
                      bool is_exit);
    void apply_to_blueprint(std::vector<RoomData> rooms,
                            LevelBlueprint& blueprint);
    void add_walls(LevelBlueprint& blueprint);
    //
    bool is_possible_to_insert_room(RoomData new_room,
                                    std::vector<RoomData> rooms);

  public:
    LevelGenerator() { srand(time(0)); }
    LevelBlueprint generate_blueprint();
    LevelBlueprint generate_full_sample_blueprint();
    LevelBlueprint generate_procedural_blueprint();
};