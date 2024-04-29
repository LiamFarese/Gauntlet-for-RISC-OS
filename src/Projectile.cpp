#include "Projectile.hpp"

#include <SDL/SDL.h>

#include "Sprite.hpp"

Projectile::Projectile(SDL_Rect position, Direction direction, SpriteClass sprite_class)
  :position_(position), direction_(direction), weapon_(sprite_class), sprite_(sprite_class) {
}

void Projectile::update(World& world){
  switch (direction_){
    case Direction::kUp:
      position_.y -= 15;
      break;
    case Direction::kDown:
      position_.y += 15;
      break;
    case Direction::kLeft:
      position_.x -= 15;
      break;
    case Direction::kRight:
      position_.x += 15;
      break;
    case Direction::kDownLeft:
      position_.x -= 15;
      position_.y += 15;
      break;
    case Direction::kDownRight:
      position_.x += 15;
      position_.y += 15;
      break;
    case Direction::kUpLeft:
      position_.x -= 15;
      position_.y -= 15;
      break;
    case Direction::kUpRight:
      position_.x += 15;
      position_.y -= 15;
      break;
  }
}