#pragma once

#include <SDL/SDL.h>
#include <unordered_map>
#include <vector>

#include "Enemy.hpp"
#include "Sprite.hpp"

enum class FloorType : Sint16 {
  Floor1 = 32,
  Floor2 = 64,
  Floor3 = 96,
  Floor4 = 128,
  Floor5 = 160,
  Floor6 = 192,
  Floor7 = 224,
  Floor8 = 256
};

enum class WallType : Sint16 {
  Wall1 = 32,
  Wall2 = 64,
  Wall3 = 96,
  Wall4 = 128,
  Wall5 = 160,
  Wall6 = 192
};

enum class TileType : Sint16 {
  Blank = 0,
  Floor,
  Verticle = 128,
  TopLeftCorner = 224,
  Horizontal = 352,
  TopRightCorner = 448,
  BottomRightCorner = 320,
  BottomLeftCorner = 64
};

namespace Level {

  struct Map {
    std::vector<std::vector<bool>> tile_map;
    SDL_Rect player_position;
    std::vector<Enemy> enemy_positions;
  };

  Map load_level(int level_number);

};