#pragma once

constexpr unsigned char CELL_SIZE = 16;   // cell in pixel
constexpr unsigned char FONT_HEIGHT = 16; // font in pixel

constexpr unsigned char GHOST_1_CHASE = 2; // Pink ghost target block
constexpr unsigned char GHOST_2_CHASE = 1; // Pink ghost target block
constexpr unsigned char GHOST_3_CHASE = 4; // Pink ghost target block

constexpr unsigned char GHOST_ANIMATION_FRAMES = 6; // ghost framecount
constexpr unsigned char GHOST_ANIMATION_SPEED = 4;  // ghost framerate
constexpr unsigned char GHOST_ESCAPE_SPEED = 4;     // ghost speed when escape
constexpr unsigned char GHOST_FRIGHTENED_SPEED = 3; // how many frame per movement{lower->faster}

constexpr unsigned char GHOST_SPEED = 1;
constexpr unsigned char MAP_HEIGHT = 21;
constexpr unsigned char MAP_WIDTH = 21;
constexpr unsigned char PACMAN_ANIMATION_FRAMES = 6;
constexpr unsigned char PACMAN_ANIMATION_SPEED = 4;
constexpr unsigned char PACMAN_DEATH_FRAMES = 12;
constexpr unsigned char PACMAN_SPEED = 2;
constexpr unsigned char SCREEN_RESIZE = 2;

constexpr unsigned short CHASE_DURATION = 1024;
constexpr unsigned short ENERGIZER_DURATION = 512;
constexpr unsigned short FRAME_DURATION = 16667;
constexpr unsigned short GHOST_FLASH_START = 64;
constexpr unsigned short LONG_SCATTER_DURATION = 512;
constexpr unsigned short SHORT_SCATTER_DURATION = 256;

enum Cell
{
  Door,
  Empty,
  Energizer,
  Pellet,
  Wall
};

struct Position
{
  short x;
  short y;

  // See? I'm an expert.
  bool operator==(const Position &i_position)
  {
    return this->x == i_position.x && this->y == i_position.y;
  }
};