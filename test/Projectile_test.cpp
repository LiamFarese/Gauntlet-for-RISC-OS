#ifdef RUNNING_TESTS

#include <cassert>
#include "../src/Projectile.hpp"

void test_projectile_creation() {
  SDL_Rect location = {100, 100, 20, 20};
  Projectile projectile{location, Direction::kUp, SpriteClass::kProjectileSprite, 1};
  
  // Check if the position, direction, and other properties are set correctly
  assert(projectile.get_position().x == 100);
  assert(projectile.get_position().y == 100);
  assert(projectile.get_position().w == 20);
  assert(projectile.get_position().h == 20);
  assert(projectile.direction_ == Direction::kUp);
  assert(projectile.collided_ == false);
  assert(projectile.destroyed_ == false);
  assert(projectile.id_ == 1);
  
  // Ensure sprite is initialized correctly
  assert(projectile.sprite_.get_frame().x == 0); // Assuming initial frame x-coordinate is 0
  assert(projectile.sprite_.get_frame().y == 0); // Assuming initial frame y-coordinate is 0
  assert(projectile.sprite_.get_frame().w == 32);
  assert(projectile.sprite_.get_frame().h == 32);
}

void test_projectile_movement() {
  SDL_Rect location = {100, 100, 20, 20};
  Projectile projectile{location, Direction::kUp, SpriteClass::kProjectileSprite, 1};
  
  // Move the projectile and check if its position changes according to its direction and speed
  projectile.update();
  assert(projectile.get_position().x == 100); //
  assert(projectile.get_position().y == 92); //
  
  // You can add more movement tests for different directions
}

#endif