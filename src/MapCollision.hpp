#pragma once
// #include "Global.hpp"

bool map_collision(bool i_collect_pallets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map);