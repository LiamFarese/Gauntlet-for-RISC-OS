#include "World.hpp"

#include <thread>

#include "Door.hpp"
#include "Models.hpp"
#include "Player.hpp"
#include "Vector2.hpp"


World::World(PlayerClass player_class) 
  : player_(new Player(player_class)) {
}

World::~World() {
}

// Loads information about the level from the Level namespace
void World::load_level(int level_id){
  Level::Map map_ = Level::load_level(level_id);
  player_->set_position(map_.player_position);
  player_->set_last_state(map_.player_state);
  enemies_ = std::move(map_.enemies);
  pickups_ = std::move(map_.pickups);
  doors_   = std::move(map_.doors);
  tile_map_ = std::move(map_.tile_map);
  level_name_ = map_.level_name;

  // Ensures projectiles do not persist to the next level or if the user backs out to menu
  player_projectiles_.clear();
  enemy_projectiles_.clear();
}

void World::update_enemies() {
  for(auto it = enemies_.begin(); it != enemies_.end(); ) {
    it->update(*this);
    if (it->is_dead()) {
      it = enemies_.erase(it);
    } else {
      ++it;
    }
  }
}

void World::update_projectiles(std::vector<Projectile>& projectiles) {
  for(auto it = projectiles.begin(); it != projectiles.end(); ) {
    it->update(*this);
    if (it->destroyed_) {
      it = projectiles.erase(it);
    } else {
      ++it;
    }
  }
}

void World::update() {
  player_->update(*this);

  update_enemies();
  update_projectiles(player_projectiles_);
  update_projectiles(enemy_projectiles_);
  
  handle_collisions();
}

template<typename T, typename C>
bool World::check_collisions(const T& a, const C& b) const {
  const SDL_Rect a_position = a.get_position();
  const SDL_Rect b_position = b.get_position();

  if(a_position.x + a_position.w < b_position.x ||
    a_position.x > b_position.x + b_position.w ||
    a_position.y + a_position.h < b_position.y ||
    a_position.y > b_position.y + b_position.h) {
      return false;
    }
  return true;
}

// Terrain collision is represented by vector<vector<bool>>, this function checks
// that tiles the entity occupies are not true (blocked)
template<typename T>
bool World::wall_collision(const T& t) const {

  const SDL_Rect p = t.get_position();
  // Each tile is 32*32 pixels
  // If entity isn't perfectly on a tile it will check the next tile in the direction
  const int y_overshot = p.y % kTileSize;
  const int x_overshot = p.x % kTileSize;

  const int y_index = p.y / kTileSize;
  const int x_index = p.x / kTileSize;

  std::vector<const std::vector<bool>*> collided_grid;

  std::vector<bool> collided_tiles {};

  collided_grid.push_back(&tile_map_[y_index]);
  if (y_overshot != 0) {
    collided_grid.push_back(&tile_map_[y_index + 1]);
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

// Opens a door if the player collides with it and has a key
bool World::collide_door(const Player& player, const Door& door) const {
  const SDL_Rect player_location = player_->get_position();
    // Check for collision with the door
  for (const auto& rect : door.location) {
    // Adjust collision detection logic
    if (!(player_location.x + player_location.w + 8 < rect.x ||
        player_location.x > rect.x + 40 ||
        player_location.y + player_location.h + 8 < rect.y ||
        player_location.y > rect.y + 40)){
          return true;
    }
  }
  return false;
}

// Updates tile map so that the location doors are placed are set false
void World::open_door(const Door& door){
  for(const auto& door_segment : door.location){
    // Each tile is 32*32 pixels
    tile_map_[door_segment.y/kTileSize][door_segment.x/kTileSize] = false;
  }
}

void World::handle_collisions() {

  // Handle Player-Wall collision
  if(wall_collision(*player_)){
    player_->set_position(player_->get_last_position());
  }

  // Player colliding with door
  for(auto door = doors_.begin(); door != doors_.end();){
    if(collide_door(*player_, *door) && player_->open_door()){
      open_door(*door);
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
      player_->set_position(player_->get_last_position());
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


