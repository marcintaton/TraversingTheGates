#pragma once

#include <algorithm>
#include <array>
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

enum class Direction { UP, DOWN, LEFT, RIGHT, EVEN };
struct Position {
    int x;
    int y;
};
struct WeightedPosition {
    int x;
    int y;
    int weigth;
};

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
    void apply_rooms_to_blueprint(std::vector<RoomData> rooms,
                                  LevelBlueprint& blueprint);
    void
    apply_corridors_to_bluerint(std::vector<std::vector<Position>> corridors,
                                LevelBlueprint& blueprint);
    void add_walls(LevelBlueprint& blueprint);
    std::vector<Position> make_corridor(RoomData start_room, RoomData end_room,
                                        LevelBlueprint room_bp);
    Position find_random_point_in_wall(RoomData room, Direction wall);
    bool find_entry_point(std::vector<Position>& corridor,
                          std::vector<Position>& visited, Position current_tile,
                          Position entry_point, LevelBlueprint bp);
    Position extrude_point(Position point, Direction dir, int by);
    std::vector<Position> dig_corridor(Position start, Direction start_dir,
                                       Position end, Direction end_dir,
                                       LevelBlueprint room_bp);

    //
    bool is_possible_to_insert_room(RoomData new_room,
                                    std::vector<RoomData> rooms);

  public:
    LevelGenerator() { srand(time(0)); }
    LevelBlueprint generate_blueprint();
    LevelBlueprint generate_full_sample_blueprint();
    LevelBlueprint generate_procedural_blueprint();
};