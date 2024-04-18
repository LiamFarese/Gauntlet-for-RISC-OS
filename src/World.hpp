#pragma once

#include <memory>
#include <vector>

#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"

class Player;

class World {

public:

  World();
  ~World();

  void update();

  std::vector<Enemy> enemies_;
  std::vector<Projectile> enemy_projectiles_;
  std::vector<Projectile> player_projectiles_;

  Player* player_;


private:

};