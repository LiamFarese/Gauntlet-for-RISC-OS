#include "Projectile.hpp"

Projectile::Projectile(SDL_Rect position, Direction direction, SpriteClass sprite_class)
  :position_(position), direction_(direction), sprite_(sprite_class) {
    // switch(sprite_class){
    //   case SpriteClass::kWarrior:
    //     sprite_.set_animation()
    //   case SpriteClass::kValkyrie:
    //   case SpriteClass::kWizard:
    //   case SpriteClass::kElf:
    //   case SpriteClass::kDemon:
    //   case SpriteClass::kDarkWizard:
    //     break;
    //   default:
    //     break;
    // }
    // sprite_.set_animation()
    // sprite_.sprite_class_ = SpriteClass::kValkyrie;
    sprite_.set_animation(AnimationState::kAxe);
}

void Projectile::move(int pixels) {
  switch (direction_){
    case Direction::kUp:
      position_.y -= pixels;
      break;
    case Direction::kDown:
      position_.y += pixels;
      break;
    case Direction::kLeft:
      position_.x -= pixels;
      break;
    case Direction::kRight:
      position_.x += pixels;
      break;
    case Direction::kDownLeft:
      position_.x -= pixels;
      position_.y += pixels;
      break;
    case Direction::kDownRight:
      position_.x += pixels;
      position_.y += pixels;
      break;
    case Direction::kUpLeft:
      position_.x -= pixels;
      position_.y -= pixels;
      break;
    case Direction::kUpRight:
      position_.x += pixels;
      position_.y -= pixels;
      break;
  }
}

void Projectile::update(World& world){
  move(20);
  sprite_.update();
}