#include "World.hpp"
#include "Projectile.hpp"
#include "SDL/SDL_video.h"

World::World() {
  player_ = new Player();
}

World::~World() {
  delete player_;
}

void World::load_level(int level_id){
  map_ = Level::load_level(level_id);
  // world_.player_->set_position(96,128);
  // world_.player_->select_player_class(PlayerClass::kWizard);
  // world_.player_->last_state_ = AnimationState::kIdleDown;
  // enemies_.push_back(std::move(Enemy{EnemyClass::kDarkWizard, {480, 96}}));
  // TODO:
  // Load position of entities
}

void World::update() {
  player_->update(*this);

  // Update enemies
  for(auto it = enemies_.begin(); it != enemies_.end(); ) {
    it->update(*this);
    if (it->dead_) {
      it = enemies_.erase(it); // Remove dead enemy
    } else {
      ++it;
    }
  }

  // Update player projectiles
  for(auto it = player_projectiles_.begin(); it != player_projectiles_.end(); ) {
    it->update(*this);
    if (it->destroyed_) {
      it = player_projectiles_.erase(it); // Remove dead enemy
    } else {
      ++it;
    }
  }

  // Update enemy projectiles
  for(auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end(); ) {
    it->update(*this);
    if (it->destroyed_) {
      it = enemy_projectiles_.erase(it); // Remove dead enemy
    } else {
      ++it;
    }
  }

  handle_collisions();
}

bool World::check_collisions(const Actor& a, const Actor& b) const {
  if(a.position_.x + a.position_.w < b.position_.x ||
    a.position_.x > b.position_.x + b.position_.w ||
    a.position_.y + a.position_.h < b.position_.y ||
    a.position_.y > b.position_.y + b.position_.h) {
      return false;
    }
  return true;
}

bool World::check_collisions(const Projectile& p, const Actor& a) const {
  if(p.position_.x + p.position_.w < a.position_.x ||
    p.position_.x > a.position_.x + a.position_.w ||
    p.position_.y + p.position_.h < a.position_.y ||
    p.position_.y > a.position_.y + a.position_.h) {
      return false;
    }
  return true;
}

bool World::wall_collision(const Actor& a) const {
  int y_overshot = a.position_.y % 32;
  int x_overshot = a.position_.x % 32;

  int y_index = a.position_.y / 32;
  int x_index = a.position_.x / 32;

  std::vector<const std::vector<bool>*> collided_grid;

  std::vector<bool> collided_tiles {};

  if (y_overshot != 0) {
    collided_grid.push_back(&map_.tile_map[y_index + 1]);
  }
  collided_grid.push_back(&map_.tile_map[y_index]);

  for(const auto& row : collided_grid){
    collided_tiles.push_back((*row)[x_index]);
    if (x_overshot != 0){
      collided_tiles.push_back((*row)[x_index + 1]);
    }
  }

  for(const auto& tile : collided_tiles){
    if(tile){
      return true;
    }
  }

  return false;
}

bool World::wall_collision(const Projectile& p) const {
  int y_overshot = p.position_.y % 32;
  int x_overshot = p.position_.x % 32;

  int y_index = p.position_.y / 32;
  int x_index = p.position_.x / 32;

  std::vector<const std::vector<bool>*> collided_grid;

  std::vector<bool> collided_tiles {};

  collided_grid.push_back(&map_.tile_map[y_index]);
  if (y_overshot != 0) {
    collided_grid.push_back(&map_.tile_map[y_index + 1]);
  }

  for(const auto& row : collided_grid){
    collided_tiles.push_back((*row)[x_index]);
    if (x_overshot != 0){
      collided_tiles.push_back((*row)[x_index + 1]);
    }
  }

  for(const auto& tile : collided_tiles){
    if(tile){
      return true;
    }
  }

  return false;
}

void World::handle_collisions() {

  // Handle Player-Wall collision
  if(wall_collision(*player_)){
    player_->position_ = player_->last_position_;
  }

  // Handle enemy-wall collision
  for (auto enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy) {
    if (wall_collision(*enemy)) {
      enemy->position_ = enemy->last_position_;
    }
  }
  
  // Handle player projectile - wall collision
  for (auto it = player_projectiles_.begin(); it != player_projectiles_.end(); ) {
    if(!it->collided_ && wall_collision(*it)){
      it->destruct();
    } else {
      ++it;
    }
  }

  // Handle enemy projectile - wall collision
  for (auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end(); ) {
    if(!it->collided_ && wall_collision(*it)){
      it->destruct();
    } else {
      ++it;
    }
  }


  // Handle collisions between player projectiles and enemies
  for (auto it = player_projectiles_.begin(); it != player_projectiles_.end(); ) {
    bool projectile_removed = false;
    for (auto it_enemy = enemies_.begin(); it_enemy != enemies_.end(); ++it_enemy) {
      if (!it_enemy->dying_ && check_collisions(*it, *it_enemy)) {
        it = player_projectiles_.erase(it);
        it_enemy->death();
        projectile_removed = true;
        break;
      }
    }
    if (!projectile_removed) {
      ++it;
    }
  }

  // Handle collisions between enemy projectiles and enemies
  for (auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end(); ) {
    bool projectile_removed = false;
    for (auto it_enemy = enemies_.begin(); it_enemy != enemies_.end(); ++it_enemy) {
      if (check_collisions(*it, *it_enemy)) {
        it = enemy_projectiles_.erase(it);
        projectile_removed = true;
        break;
      }
    }
    if (!projectile_removed) {
      ++it;
    }
  }

  // Handle collisions between player and enemies
  for (auto enemy = enemies_.begin(); enemy != enemies_.end(); ) {
    if (!enemy->dying_ && check_collisions(*player_, *enemy)) {
      // Damage player
      enemy->death();
    } else {
      ++enemy;
    }
  }

  // Handle collisions between enemy projectiles and player
  for (auto enemy_proj = enemy_projectiles_.begin(); enemy_proj != enemy_projectiles_.end(); ) {
    if (!enemy_proj->collided_ && check_collisions(*enemy_proj, *player_)) {
      // Damage player
      enemy_proj->destruct();
    } else {
      ++enemy_proj;
    }
  }
}