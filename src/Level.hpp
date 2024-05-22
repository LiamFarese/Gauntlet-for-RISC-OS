#pragma once

#include <SDL/SDL.h>
#include <unordered_map>
#include <vector>

#include "Enemy.hpp"
#include "Sprite.hpp"

namespace Level {

  struct Map {
    std::vector<std::vector<bool>> tile_map;
    SDL_Rect player_position;
    AnimationState player_state;
    std::vector<Enemy> enemies;
    std::string level_name;
  };

  Map load_level(int level_number);

};