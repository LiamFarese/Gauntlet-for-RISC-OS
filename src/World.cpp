#include "World.hpp"
#include "Projectile.hpp"

World::World() {
  player_ = new Player();
}

World::~World() {
  delete player_;
}

void World::load_level(int level_id){
  map_ = Level::load_level(level_id);
  Enemy enemy {EnemyClass::kDarkWizard};
  enemy.set_position(400, 400);
  enemy.sprite_.sprite_class_ = SpriteClass::kDarkWizard;
  enemy.sprite_.set_animation(AnimationState::kIdleDown);
  enemies_.push_back(std::move(enemy));
  // TODO:
  // Load position of entities
}

void World::update() {
  player_->update(*this);

  for(auto& enemy: enemies_){
    enemy.update(*this);
  }
  for(auto& projectile: player_projectiles_){
    projectile.update(*this);
  }

  for(auto& projectile: enemy_projectiles_){
    projectile.update(*this);
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

  std::vector<const std::vector<Tile>*> collided_grid;

  Tile collided_tile {};
  std::vector<Tile> collided_tiles {};

  if (y_overshot != 0) {
    collided_grid.push_back(&map_.tile_map[y_index + 1]);
  }
  collided_grid.push_back(&map_.tile_map[y_index]);

  for(auto& row : collided_grid){
    collided_tiles.push_back((*row)[x_index]);
    if (x_overshot != 0){
      collided_tiles.push_back((*row)[x_index + 1]);
    }
  }

  for(auto& tile : collided_tiles){
    if(tile.is_collidable == true){
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

  std::vector<const std::vector<Tile>*> collided_grid;

  Tile collided_tile {};
  std::vector<Tile> collided_tiles {};

  collided_grid.push_back(&map_.tile_map[y_index]);
  if (y_overshot != 0) {
    collided_grid.push_back(&map_.tile_map[y_index + 1]);
  }

  for(auto& row : collided_grid){
    collided_tiles.push_back((*row)[x_index]);
    if (x_overshot != 0){
      collided_tiles.push_back((*row)[x_index + 1]);
    }
  }

  for(auto& tile : collided_tiles){
    if(tile.is_collidable == true){
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
    if(wall_collision(*it)){
      it = player_projectiles_.erase(it);
    } else {
      ++it;
    }
  }

  // Handle enemy projectile - wall collision
  for (auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end(); ) {
    if(wall_collision(*it)){
      it = enemy_projectiles_.erase(it);
    } else {
      ++it;
    }
  }

  // Handle collisions between player projectiles and enemies
  for (auto it = player_projectiles_.begin(); it != player_projectiles_.end(); ) {
    bool projectile_removed = false;
    for (auto it_enemy = enemies_.begin(); it_enemy != enemies_.end(); ++it_enemy) {
      if (check_collisions(*it, *it_enemy)) {
        it = player_projectiles_.erase(it);
        it_enemy = enemies_.erase(it_enemy);
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
    if (check_collisions(*player_, *enemy)) {
      enemy = enemies_.erase(enemy);
    } else {
      ++enemy;
    }
  }

  // Handle collisions between enemy projectiles and player
  for (auto enemy_proj = enemy_projectiles_.begin(); enemy_proj != enemy_projectiles_.end(); ) {
    if (check_collisions(*enemy_proj, *player_)) {
      enemy_proj = enemy_projectiles_.erase(enemy_proj);
    } else {
      ++enemy_proj;
    }
  }

}