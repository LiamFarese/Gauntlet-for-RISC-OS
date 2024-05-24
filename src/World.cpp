#include "World.hpp"
#include "Models.hpp"
#include "Vector2.hpp"

World::World(PlayerClass player_class) 
  : player_(new Player(player_class)) {
}

World::~World() {
}

// Loads information about the level from the Level namespace
void World::load_level(int level_id){
  map_ = Level::load_level(level_id);
  player_->set_position(map_.player_position);
  player_->set_last_state(map_.player_state);
  enemies_ = std::move(map_.enemies);
  pickups_ = std::move(map_.pickups);

  // Ensures projectiles do not persist to the next level or if the user backs out to menu
  player_projectiles_.clear();
  enemy_projectiles_.clear();
}

void World::update(SDL_Rect& camera) {
  player_->update(*this);

  // Update enemies
  for(auto it = enemies_.begin(); it != enemies_.end(); ) {
    it->update(*this);
    if (it->is_dead()) {
      it = enemies_.erase(it);
    } else {
      ++it;
    }
  }

  // Update player projectiles
  for(auto it = player_projectiles_.begin(); it != player_projectiles_.end(); ) {
    it->update(*this);
    if (it->destroyed_) {
      it = player_projectiles_.erase(it);
    } else {
      ++it;
    }
  }

  // Update enemy projectiles
  for(auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end(); ) {
    it->update(*this);
    if (it->destroyed_) {
      it = enemy_projectiles_.erase(it);
    } else {
      ++it;
    }
  }
  
  handle_collisions();
}

template<typename T, typename C>
bool World::check_collisions(const T& a, const C& b) const {
  SDL_Rect a_position = a.get_position();
  SDL_Rect b_position = b.get_position();

  if(a_position.x + a_position.w -1 < b_position.x ||
    a_position.x > b_position.x + b_position.w -1 ||
    a_position.y + a_position.h -1 < b_position.y ||
    a_position.y > b_position.y + b_position.h -1) {
      return false;
    }
  return true;
}


// Terrain collision is represented by vector<vector<bool>>, this function checks
// that tiles the entity occupies are not true (blocked)
template<typename T>
bool World::wall_collision(const T& t) const {

  SDL_Rect p = t.get_position();
  // If entity isn't perfectly on a tile it will check the next tile in the direction
  int y_overshot = p.y % 32;
  int x_overshot = p.x % 32;

  int y_index = p.y / 32;
  int x_index = p.x / 32;

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

bool World::collide_door(const Player& player, const Door& door) const {
  SDL_Rect player_location = player_->get_position();
  for(const auto& rect : door.Location){
    if(!(player_location.x + player_location.w -1 < rect.x ||
        player_location.x > rect.x + rect.w -1 ||
        rect.y + player_location.h -1 < rect.y ||
        rect.y > rect.y + rect.h -1)) {
          return true;
      }
  }
  return false;
}

void World::handle_collisions() {

  // Handle Player-Wall collision
  if(wall_collision(*player_)){
    player_->set_position(player_->get_last_position());
  }

  // Player colliding with door
  for(auto door = doors_.begin(); door != doors_.end();){
    if(collide_door(*player_, *door) && player_->open_door()){
      door = doors_.erase(door);
      player_->notify(GameEvent::kOpenDoor);
    } else {
      ++door;
    }
  }

  // Handle enemy-wall collision
  for (auto enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy) {
    if (wall_collision(*enemy)) {
      enemy->set_position(enemy->get_last_position());
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

  // Handle player collision with pickups
  for(auto pickup = pickups_.begin(); pickup != pickups_.end();){
    if(check_collisions(*pickup, *player_)){
      player_->pickup_item(*pickup);
      pickup = pickups_.erase(pickup);
    } else {
      ++pickup;
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
      if (!it_enemy->is_dying() && check_collisions(*it, *it_enemy)) {
        it = player_projectiles_.erase(it);
        it_enemy->death();
        player_->notify(GameEvent::kEnemyDestroyed);
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
      if (check_collisions(*it, *it_enemy) && it->id_ != it_enemy->id_) {
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
    if (!enemy->is_dying() && check_collisions(*player_, *enemy)) {
      player_->damage();
      player_->notify(GameEvent::kEnemyDestroyed);
      enemy->death();
    } else {
      ++enemy;
    }
  }

  // Handle collisions between enemy projectiles and player
  for (auto enemy_proj = enemy_projectiles_.begin(); enemy_proj != enemy_projectiles_.end(); ) {
    bool projectile_removed = false;
    if (!enemy_proj->collided_ && check_collisions(*enemy_proj, *player_)) {
      player_->damage();
      enemy_proj = enemy_projectiles_.erase(enemy_proj);
        projectile_removed = true;
        break;
      }
    if (!projectile_removed) {
      ++enemy_proj;
    }
  }
}


