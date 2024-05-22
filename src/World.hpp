#pragma once

#include <memory>
#include <vector>

#include <SDL/SDL.h>


#include "Level.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"

class Player;

class World {

public:

  World();
  World(PlayerClass player_class);
  ~World();

  void update(SDL_Rect& camera);
  void load_level(int level_id);

  std::vector<Enemy> enemies_;
  std::vector<Projectile> enemy_projectiles_;
  std::vector<Projectile> player_projectiles_;
  Level::Map map_;
  Player* player_;

private:

  bool check_collisions(const Actor& a, const Actor& b) const;
  bool check_collisions(const Projectile& p, const Actor& a) const;
  bool wall_collision(const Actor& a) const;
  bool wall_collision(const Projectile& p) const;
  void handle_collisions();
  void apply_seperation();
};