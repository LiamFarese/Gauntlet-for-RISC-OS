#pragma once

#include <memory>
#include <vector>
#include <SDL/SDL.h>

#include "Door.hpp"
#include "Level.hpp"
#include "Pickup.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "SoundManager.hpp"
#include "Sprite.hpp"
#include "UIManager.hpp"

class Player;

// The World class manages the game world state, including the player, enemies, projectiles, and pickups.
class World {

public:
  // Constructor and destructor
  World(PlayerClass player_class);
  ~World();

  // Method to update the world state, takes camera as a parameter to cull updates on offscreen enemies
  void update(SDL_Rect& camera);

  // Method to load a new level
  void load_level(int level_id);

  // Level name
  std::string level_name_;
  
  // Exposed entities for renderer
  std::unique_ptr<Player> player_;
  std::vector<Enemy> enemies_;
  std::vector<Projectile> enemy_projectiles_;
  std::vector<Projectile> player_projectiles_;
  std::vector<Pickup> pickups_;
  std::vector<Door> doors_;

  // Terrain collision
  std::vector<std::vector<bool>> tile_map_;

private:
  // Entity collision detection, to be used between actors, projectiles and pickups
  template<typename T, typename C>
  bool check_collisions(const T& a, const C& b) const;

  // Door collision
  bool collide_door(const Player& player, const Door& door) const;

  // Remove door from terrain
  void open_door(const Door& door);

  // Wall collision detection, to be used on actor or projectile
  template<typename T>
  bool wall_collision(const T& t) const;

  // Private methods to handle collisions and apply separation between entities
  void handle_collisions();
};
