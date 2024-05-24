#include "Level.hpp"
#include "Enemy.hpp"
#include "Pickup.hpp"

namespace {

  const std::vector<std::vector<int>> training_1 {
    {71, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 77},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {68, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {71, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 74, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {72, 74, 7, 7, 7, 68, 79, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 74},
    {70, 7, 7, 7, 7, 7, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {70, 7, 7, 7, 7, 7, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {70, 7, 7, 7, 7, 7, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {70, 7, 7, 7, 7, 7, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {70, 7, 7, 7, 7, 7, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {70, 7, 7, 7, 7, 7, 72, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77},
    {70, 7, 7, 7, 7, 7, 66, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {70, 7, 7, 7, 7, 7, 69, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {68, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 78, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 71, 75, 77, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 78, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 66, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 69, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 68, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 74}
  };

  std::vector<Enemy> init_enemies(int level_id){
    std::vector<Enemy> enemies;
    switch (level_id) {
      case 0:
        enemies.reserve(50);
        enemies.emplace_back(Enemy{EnemyClass::kDemon, {400, 128, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kBoxer, {432, 128, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {500, 128, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {64, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {104, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {144, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {184, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {224, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {264, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {304, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {344, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {384, 460, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {424, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {464, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {504, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {544, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {584, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {624, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {664, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {704, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {744, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {784, 420, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {824, 420, 32, 32}});
        // Second area
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {330, 800, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {232, 800, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {264, 800, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {296, 800, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {264, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {304, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {344, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {384, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {424, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {464, 850, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {504, 860, 32, 32}});
        enemies.emplace_back(Enemy{EnemyClass::kGhost, {544, 860, 32, 32}});
        // Third area
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {584, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {624, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {664, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {704, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {744, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {784, 420, 32, 32}});
        // enemies.emplace_back(Enemy{EnemyClass::kGhost, {824, 420, 32, 32}});
        break;
    }
    return enemies;
  }
}

Level::Map Level::load_level(int level_number) {
  std::vector<std::vector<int>> grid;

  Map map{};

  switch (level_number) {
    case 0:
      map.level_number = 0;
      map.level_name = "<!Gauntlet$Dir>.training1";
      grid = training_1;
      map.player_position = {96, 128, 32, 32};
      map.player_state = AnimationState::kIdleDown;
      map.enemies = std::move(init_enemies(0));
      map.pickups = {Pickup{PickupType::kPoints, {600, 33, 32, 32}},
                     Pickup{PickupType::kPoints, {1216, 544, 32, 32}},
                     Pickup{PickupType::kPoints, {1216, 1312, 32, 32}},
                     Pickup{PickupType::kPoints, {32, 928, 32, 32}},
                     Pickup{PickupType::kExit, {192, 1152, 32, 32}}
      };
      break;
    default:
      break;
  }

  map.tile_map.reserve(grid.size());

  for (const auto& row : grid) {
    std::vector<bool> level_row;
    level_row.reserve(row.size());

    for (const auto& tile_id : row) {
      level_row.push_back(tile_id > 10);
    }
    map.tile_map.push_back(std::move(level_row));
  }

  return map;
}

