#include "Level.hpp"
#include "Enemy.hpp"

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
    {1, 1, 1, 1, 1, 70, 7, 68, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 78, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 66, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 70, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 69, 7, 7, 7, 7, 7, 70},
    {1, 1, 1, 1, 1, 68, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 74}
  };
}

Level::Map Level::load_level(int level_number) {
  std::vector<std::vector<int>> grid;

  Map map{};

  switch (level_number) {
    case 0:
      map.level_number = 0;
      map.level_name = "<!Gauntlet$Dir>.training1";
      grid = training_1;  // Directly use a reference to the static grid
      map.player_position = {96, 128, 32, 32};
      map.player_state = AnimationState::kIdleDown;
      map.enemies.reserve(30);  // Reserve space for 30 enemies
      map.enemies.emplace_back(Enemy{EnemyClass::kDemon, {400, 128, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kBoxer, {432, 128, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {500, 128, 32, 32}});
      // map.enemies.emplace_back(Enemy{EnemyClass::kDarkWizard, {300, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {64, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {104, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {144, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {184, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {224, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {264, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {304, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {344, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {384, 460, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {424, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {464, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {504, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {544, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {584, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {624, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {664, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {704, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {744, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {784, 420, 32, 32}});
      map.enemies.emplace_back(Enemy{EnemyClass::kGhost, {824, 420, 32, 32}});
      break;
    default:
      break;
  }

  map.tile_map.reserve(grid.size());  // Reserve space for rows in the tile_map

  for (const auto& row : grid) {
    std::vector<bool> level_row;
    level_row.reserve(row.size());  // Reserve space for columns in each row

    for (const auto& tile_id : row) {
      level_row.push_back(tile_id > 10);
    }
    map.tile_map.push_back(std::move(level_row));
  }

  return map;
}

