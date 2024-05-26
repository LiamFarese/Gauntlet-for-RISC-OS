#pragma once

#include <SDL/SDL.h>
#include <unordered_map>
#include <vector>

#include "Door.hpp"
#include "Enemy.hpp"
#include "Pickup.hpp"
#include "Sprite.hpp"

namespace Level {

  struct Map {
    std::vector<std::vector<bool>> tile_map;
    SDL_Rect player_position;
    AnimationState player_state;
    std::vector<Enemy> enemies;
    std::vector<Pickup> pickups;
    std::vector<Door> doors;
    std::string level_name;
    int level_number;
  };

  Map load_level(int level_number);

};