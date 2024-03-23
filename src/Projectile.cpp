#include "Projectile.hpp"

#include <SDL/SDL.h>

#include "Sprite.hpp"

Projectile::Projectile(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Rect position, Direction direction,
  SpriteClass sprite_class)
  :sprite_(), screen_(screen), position_(position), direction_(direction), weapon_(sprite_class){
  sprite_.set_sprite_class(sprite_class);
}

void Projectile::update(){
  switch (direction_){
    case Direction::kUp:
      position_.y -= 4;
      break;
    case Direction::kDown:
      position_.y += 4;
      break;
    case Direction::kLeft:
      position_.x -= 4;
      break;
    case Direction::kRight:
      position_.x += 4;
      break;
    case Direction::kDownLeft:
      position_.x -= 4;
      position_.y += 4;
      break;
    case Direction::kDownRight:
      position_.x += 4;
      position_.y += 4;
      break;
    case Direction::kUpLeft:
      position_.x -= 4;
      position_.y -= 4;
      break;
    case Direction::kUpRight:
      position_.x += 4;
      position_.y -= 4;
      break;
  }
}

// void Projectile::render(){
//   sprite_.render(screen_, position_.x, position_.y);
// }