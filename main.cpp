#include <SFML/Graphics.hpp>
#include <array>
#include <ctime>
#include <chrono>

#include "Global.hpp"
#include "GhostManager.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"
#include "DrawMap.hpp"
#include "DrawText.hpp"
#include "MapCollision.hpp"
#include "ConvertSketch.hpp"
//
int main()
{
  bool game_won = 0;       // is game won?
  unsigned lag = 0;        // framerate-independent
  unsigned char level = 0; // level

  // Similar to lag, used to make the game framerate-independent.
  std::chrono::time_point<std::chrono::steady_clock> previous_time;

  // std::array<std::string, MAP_HEIGHT> map_sketch = {
  //     "############################",
  //     "#............##............#",
  //     "#.####.#####.##.#####.####.#",
  //     "#o####.#####.##.#####.####o#",
  //     "#.####.#####.##.#####.####.#",
  //     "#..........................#",
  //     "#.####.##.########.##.####.#",
  //     "#.####.##.########.##.####.#",
  //     "#......##....##....##......#",
  //     "######.##### ## #####.######",
  //     "######.##### ## #####.######",
  //     "######.##          ##.######",
  //     "######.##    0     ##.######",
  //     "######.## ###==### ##.######",
  //     "      .   # 123  #   .      ",
  //     "######.## ######## ##.######",
  //     "######.##          ##.######",
  //     "######.## ######## ##.######",
  //     "######.## ######## ##.######",
  //     "#............##............#",
  //     "#.####.#####.##.#####.####.#",
  //     "#.####.#####.##.#####.####.#",
  //     "#o..##.......p.......##..o#",
  //     "###.##.##.########.##.##.###",
  //     "###.##.##.########.##.##.###",
  //     "#......##....##....##......#",
  //     "#.##########.##.##########.#",
  //     "#..........................#",
  //     "############################",
  // };
  std::array<std::string, MAP_HEIGHT> map_sketch = {
      " ################### ",
      " #........#........# ",
      " #o##.###.#.###.##o# ",
      " #.................# ",
      " #.##.#.#####.#.##.# ",
      " #....#...#...#....# ",
      " ####.### # ###.#### ",
      "    #.#   0   #.#    ",
      "#####.# ##=## #.#####",
      "     .  #123#  .     ",
      "#####.# ##### #.#####",
      "    #.#       #.#    ",
      " ####.# ##### #.#### ",
      " #........#........# ",
      " #.##.###.#.###.##.# ",
      " #o.#.....P.....#.o# ",
      " ##.#.#.#####.#.#.## ",
      " #....#...#...#....# ",
      " #.######.#.######.# ",
      " #.................# ",
      " ################### "};

  std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};
  // 0.2625-0.175-0.0875
  std::array<Position, 4> ghost_positions; // ghost home position
  sf::Event event;                         // sfml event

  // set window
  sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
  window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

  // create manager;
  GhostManager ghost_manager;
  Pacman pacman;
  // Generate seed
  srand(static_cast<unsigned>(time(0)));

  map = convert_sketch(map_sketch, ghost_positions, pacman);
  ghost_manager.reset(level, ghost_positions);
  previous_time = std::chrono::steady_clock::now();

  // Game loop
  while (1 == window.isOpen())
  {
    // clac the lag of the game
    unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

    lag += delta_time;
    previous_time += std::chrono::microseconds(delta_time);
    while (FRAME_DURATION <= lag)
    {
      lag -= FRAME_DURATION;
      while (1 == window.pollEvent(event))
      {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
          // Making sure the player can close the window.
          window.close();
        }
        }
      }
      // check if pacman is dead
      if (0 == game_won && 0 == pacman.get_dead())
      {
        game_won = 1;
        pacman.update(level, map);
        ghost_manager.update(level, map, pacman);
        // We're checking every cell in the map.
        for (const std::array<Cell, MAP_HEIGHT> &column : map)
        {
          for (const Cell &cell : column)
          {
            if (Cell::Pellet == cell)
            {
              game_won = 0; // The game is not yet won.
              break;
            }
          }
          if (0 == game_won)
          {
            break;
          }
        }

        if (1 == game_won)
        {
          pacman.set_animation_timer(0);
        }
      }

      // restart the game
      else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        game_won = 0;
        if (1 == pacman.get_dead())
        {
          level = 0;
        }
        else
        {
          // After each win we reduce the duration of attack waves and energizers.
          level++;
        }
        map = convert_sketch(map_sketch, ghost_positions, pacman);
        ghost_manager.reset(level, ghost_positions);
        pacman.reset();
      }

      if (FRAME_DURATION > lag)
      {
        window.clear();

        if (0 == game_won && 0 == pacman.get_dead())
        {
          draw_map(map, window);

          ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window);

          draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);
        }

        pacman.draw(game_won, window);

        if (1 == pacman.get_animation_over())
        {
          if (1 == game_won)
          {
            draw_text(1, 0, 0, "Next level!", window);
          }
          else
          {
            draw_text(1, 0, 0, "Game over", window);
          }
        }

        window.display();
      }
    }
  }
}