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

void LevelGenerator::apply_rooms_to_blueprint(std::vector<RoomData> rooms,
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

void LevelGenerator::apply_corridors_to_bluerint(
    std::vector<std::vector<Position>> corridors, LevelBlueprint& blueprint)
{
    for (auto corridor : corridors) {
        for (auto position : corridor) {
            blueprint.base_level[position.x][position.y] = 1;
        }
    }
}

void LevelGenerator::add_walls(LevelBlueprint& blueprint)
{
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (blueprint.base_level[i][j] == 0) {
                for (int k = -1; k < 2; ++k) {
                    for (int m = -1; m < 2; ++m) {
                        int x = i + k;
                        int y = j + m;

                        if ((k != 0 && m != 0) && x >= 0 && y >= 0 && x < 100 &&
                            y < 100) {
                            if (blueprint.base_level[x][y] == 1) {
                                blueprint.base_level[i][j] = 2;
                            }
                        }
                    }
                }

                if (i == 0 || j == 0 || i == 99 || j == 99) {
                    blueprint.base_level[i][j] = 2;
                }
            }
        }
    }
}

std::vector<Position> LevelGenerator::make_corridor(RoomData start_room,
                                                    RoomData end_room,
                                                    LevelBlueprint room_bp)
{
    int req_direction_offset = 5;
    //
    Direction horizontal = Direction::EVEN;
    Direction vertical = Direction::EVEN;

    if (start_room.x < end_room.x &&
        end_room.x - start_room.x > req_direction_offset) {
        horizontal = Direction::RIGHT;
    }
    if (start_room.x > end_room.x &&
        start_room.x - end_room.x > req_direction_offset) {
        horizontal = Direction::LEFT;
    }
    if (start_room.y < end_room.y &&
        end_room.y - start_room.y > req_direction_offset) {
        vertical = Direction::UP;
    }
    if (start_room.y > end_room.y &&
        start_room.y - end_room.y > req_direction_offset) {
        vertical = Direction::DOWN;
    }

    Direction start_wall;
    Direction end_wall;

    // choose room walls to extrude corridor
    if (horizontal == Direction::EVEN) {
        start_wall =
            vertical == Direction::UP ? Direction::UP : Direction::DOWN;
        end_wall = vertical == Direction::UP ? Direction::DOWN : Direction::UP;
    } else if (vertical == Direction::EVEN) {
        start_wall =
            horizontal == Direction::LEFT ? Direction::LEFT : Direction::RIGHT;
        end_wall =
            horizontal == Direction::LEFT ? Direction::RIGHT : Direction::LEFT;
    } else {
        int random_corridor_directtion_for_start = random(0, 1);
        if (random_corridor_directtion_for_start == 1) {
            start_wall = horizontal;
            end_wall =
                vertical == Direction::UP ? Direction::DOWN : Direction::UP;
        } else {
            start_wall = vertical;
            end_wall = horizontal == Direction::LEFT ? Direction::RIGHT :
                                                       Direction::LEFT;
        }
    }

    Position cor_start = find_random_point_in_wall(start_room, start_wall);
    Position cor_end = find_random_point_in_wall(end_room, end_wall);

    return dig_corridor(cor_start, start_wall, cor_end, end_wall, room_bp);
}

Position LevelGenerator::find_random_point_in_wall(RoomData room,
                                                   Direction wall)
{
    Position pos;

    if (wall == Direction::UP) {
        pos.x = random(room.x, room.x + room.w - 1);
        pos.y = room.y + room.h;
    } else if (wall == Direction::DOWN) {
        pos.x = random(room.x, room.x + room.w - 1);
        pos.y = room.y - 1;
    } else if (wall == Direction::LEFT) {
        pos.x = room.x - 1;
        pos.y = random(room.y, room.y + room.h - 1);
    } else if (wall == Direction::RIGHT) {
        pos.x = room.x + room.w;
        pos.y = random(room.y, room.y + room.h - 1);
    }

    return pos;
}

std::vector<Position>
LevelGenerator::dig_corridor(Position start, Direction start_dir, Position end,
                             Direction end_dir, LevelBlueprint room_bp)
{
    Position extruded_start_pos = extrude_point(start, start_dir, 1);
    Position extruded_end_pos = extrude_point(end, end_dir, 1);

    WeightedPosition wgh_end_pos =
        WeightedPosition {extruded_end_pos.x, extruded_end_pos.y, 1};

    std::vector<WeightedPosition> wght_pos;
    wght_pos.push_back(wgh_end_pos);

    bool is_start_reached = false;

    while (!is_start_reached) {

        for (int i = 0; i < wght_pos.size(); ++i) {
            std::array<WeightedPosition, 4> neighbours;

            for (int j = 0; j < 4; ++j) {
                neighbours[j].x = wght_pos[i].x;
                neighbours[j].y = wght_pos[i].y;
                neighbours[j].weigth = wght_pos[i].weigth + 1;
            }
            // left
            neighbours[0].x -= 1;
            // right
            neighbours[1].x += 1;
            // up
            neighbours[2].y += 1;
            // down
            neighbours[3].y -= 1;

            for (auto n : neighbours) {
                if (room_bp.base_level[n.x][n.y] == 0) {

                    bool is_present = false;
                    for (auto pos : wght_pos) {
                        if (pos.x == n.x && pos.y == n.y &&
                            pos.weigth <= n.weigth) {
                            is_present = true;
                            break;
                        }
                    }

                    if (!is_present) {
                        wght_pos.push_back(n);

                        if (n.x == extruded_start_pos.x &&
                            n.y == extruded_start_pos.y) {
                            is_start_reached = true;
                        }
                    }
                }
                if (is_start_reached == true) {
                    break;
                }
            }
            if (is_start_reached == true) {
                break;
            }
        }
    }

    //
    for (auto pos : wght_pos) {
        room_bp.base_level[pos.x][pos.y] = pos.weigth;
    }

    std::vector<Position> corridor_positions;
    std::vector<Position> visited;

    find_entry_point(corridor_positions, visited, extruded_end_pos,
                     extruded_start_pos, room_bp);

    corridor_positions.push_back(end);
    corridor_positions.push_back(start);

    return corridor_positions;
}

bool LevelGenerator::find_entry_point(std::vector<Position>& corridor,
                                      std::vector<Position>& visited,
                                      Position current_tile,
                                      Position entry_point, LevelBlueprint bp)
{

    auto found_in_visited =
        std::find_if(visited.begin(), visited.end(), [&](const Position pos) {
            return (pos.x == current_tile.x && pos.y == current_tile.y);
        });

    if (found_in_visited != visited.end()) {
        return false;
    }

    visited.push_back(current_tile);
    //
    if (current_tile.x == entry_point.x && current_tile.y == entry_point.y) {
        corridor.push_back(current_tile);
        return true;
    }

    int x = current_tile.x;
    int y = current_tile.y;
    int w = bp.base_level[x][y];

    WeightedPosition l = WeightedPosition {x - 1, y, bp.base_level[x - 1][y]};
    WeightedPosition r = WeightedPosition {x + 1, y, bp.base_level[x + 1][y]};
    WeightedPosition u = WeightedPosition {x, y + 1, bp.base_level[x][y + 1]};
    WeightedPosition d = WeightedPosition {x, y - 1, bp.base_level[x][y - 1]};

    std::vector<WeightedPosition> neighbours = {l, u, r, d};

    for (auto wp : neighbours) {

        if (wp.weigth > w) {
            Position p = Position {wp.x, wp.y};
            bool result =
                find_entry_point(corridor, visited, p, entry_point, bp);
            if (result == true) {
                corridor.push_back(current_tile);
                return true;
            }
        }
    }
    return false;
}

Position LevelGenerator::extrude_point(Position point, Direction dir, int by)
{
    Position extruded = point;
    if (dir == Direction::DOWN) {
        extruded.y -= by;
    } else if (dir == Direction::UP) {
        extruded.y += by;
    } else if (dir == Direction::LEFT) {
        extruded.x -= by;
    } else if (dir == Direction::RIGHT) {
        extruded.x += by;
    }

    return extruded;
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

    // Room generation
    std::vector<RoomData> rooms;
    // Add entry room
    while (rooms.size() == 0) {
        try_add_room(rooms, true, false);
    }
    // Add exit room
    while (rooms.size() == 1) {
        try_add_room(rooms, false, true);
    }

    int room_count = random(min_room_count, max_room_count);

    // Add random rooms
    int room_addition_tries = 0;
    while (rooms.size() != room_count) {
        try_add_room(rooms, false, false);
        room_addition_tries++;
        if (room_addition_tries > max_room_addition_tries) {
            break;
        }
    }

    apply_rooms_to_blueprint(rooms, blueprint);
    // End of Room generation

    // Prepare room navmesh
    auto room_navmesh_bp = blueprint;
    add_walls(room_navmesh_bp);
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; j++) {
            if (room_navmesh_bp.base_level[i][j] != 0) {
                room_navmesh_bp.base_level[i][j] = -1;
            }
        }
    }

    // Corridor generation
    std::vector<std::vector<Position>> corridors;
    // Corridor from start room
    corridors.push_back(make_corridor(rooms[0], rooms[2], room_navmesh_bp));

    for (int i = 2; i < rooms.size() - 1; ++i) {
        corridors.push_back(
            make_corridor(rooms[i], rooms[i + 1], room_navmesh_bp));
    }

    // // Corridor to end room
    corridors.push_back(make_corridor(rooms.back(), rooms[1], room_navmesh_bp));

    // End of corridor Generation

    apply_corridors_to_bluerint(corridors, blueprint);

    add_walls(blueprint);

    int player_x = rooms[0].x + 1;
    int player_y = rooms[0].y + 1;
    blueprint.top_level[player_x][player_y] = 3;

    return blueprint;
}
