#include "LevelGenerator.h"

#include <random>

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

int LevelGenerator::random(int min, int max)
{
    if (min == max) {
        return min;
    }
    int x = rand() % (max - min) + min;
    return x;
}

void LevelGenerator::try_add_room(std::vector<RoomData>& rooms, bool is_entry,
                                  bool is_exit)
{
    int w = random(min_room_size, max_room_size);
    int h = random(min_room_size, max_room_size);

    int pos_x = random(1, 99 - w);
    int pos_y = random(1, 99 - h);

    RoomData entry_room = RoomData {pos_x, pos_y, w, h, is_entry, is_exit};

    if (is_possible_to_insert_room(entry_room, rooms)) {
        rooms.push_back(entry_room);
    }
}

void LevelGenerator::apply_to_blueprint(std::vector<RoomData> rooms,
                                        LevelBlueprint& blueprint)
{
    for (auto room : rooms) {
        for (int i = room.x; i < room.x + room.w; ++i) {
            for (int j = room.y; j < room.y + room.h; ++j) {
                blueprint.base_level[i][j] = 1;
            }
        }
    }
}

void LevelGenerator::add_walls(LevelBlueprint& blueprint)
{
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (blueprint.base_level[i][j] == 0) {
                if (blueprint.base_level[i + 1][j + 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i + 1][j] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i + 1][j - 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i][j + 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i][j - 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i - 1][j + 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i - 1][j] == 1) {
                    blueprint.base_level[i][j] = 2;
                } else if (blueprint.base_level[i - 1][j - 1] == 1) {
                    blueprint.base_level[i][j] = 2;
                }
            }

            if (i == 0 || j == 0 || i == 99 || j == 99) {
                blueprint.base_level[i][j] = 2;
            }
        }
    }
}

bool LevelGenerator::is_possible_to_insert_room(RoomData new_room,
                                                std::vector<RoomData> rooms)
{
    // case room is out of map bounds
    if (new_room.x < 1 || new_room.y < 1 || new_room.x + new_room.w > 99 ||
        new_room.y + new_room.h > 99) {
        return false;
    }

    for (auto room : rooms) {
        // case new room entry point is in room
        if (new_room.x >= room.x && new_room.x <= room.x + room.w &&
            new_room.y >= room.y && new_room.y <= room.y + room.h) {
            return false;
        }
        // case new room left from room
        if (new_room.x + new_room.w + 3 > room.x && new_room.x < room.x) {
            return false;
        }
        // case new room right from room
        if (new_room.x > room.x && new_room.x < room.x + room.w + 3) {
            return false;
        }
        // case new room below room
        if (new_room.y + new_room.h + 3 > room.y && new_room.y < room.y) {
            return false;
        }
        // case new room above room
        if (new_room.y > room.y && new_room.y < room.y + room.w + 3) {
            return false;
        }
    }

    return true;
}

LevelBlueprint LevelGenerator::generate_procedural_blueprint()
{
    auto blueprint = LevelBlueprint();

    std::vector<RoomData> rooms;

    while (rooms.size() == 0) {
        try_add_room(rooms, true, false);
    }

    while (rooms.size() == 1) {
        try_add_room(rooms, false, true);
    }

    int room_count = random(min_room_count, max_room_count);

    int room_addition_tries = 0;
    while (rooms.size() != room_count) {
        try_add_room(rooms, false, false);
        room_addition_tries++;
        if (room_addition_tries > max_room_addition_tries) {
            break;
        }
    }

    apply_to_blueprint(rooms, blueprint);
    //
    add_walls(blueprint);

    int player_x = rooms[0].x + 1;
    int player_y = rooms[0].y + 1;
    blueprint.top_level[player_x][player_y] = 3;

    return blueprint;
}
