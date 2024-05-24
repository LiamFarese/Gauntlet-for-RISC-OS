#include "Projectile.hpp"

Projectile::Projectile(SDL_Rect position, Direction direction, SpriteClass sprite_class, int id)
  : sprite_(sprite_class), position_(position), direction_(direction), collided_(false), destroyed_(false), id_(id) {
    if(sprite_class == SpriteClass::kWarrior){
      sprite_.set_animation(AnimationState::kAxe);
    } else {
      switch (direction) {
        case Direction::kUp:
          sprite_.set_animation(AnimationState::kProjectileUp); break;
        case Direction::kDown:
          sprite_.set_animation(AnimationState::kProjectileDown); break;
        case Direction::kLeft:
          sprite_.set_animation(AnimationState::kProjectileLeft); break;
        case Direction::kRight:
          sprite_.set_animation(AnimationState::kProjectileRight); break;
        case Direction::kUpRight:
          sprite_.set_animation(AnimationState::kProjectileUpRight); break;
        case Direction::kUpLeft:
          sprite_.set_animation(AnimationState::kProjectileUpLeft); break;
        case Direction::kDownLeft:
          sprite_.set_animation(AnimationState::kProjectileDownLeft); break;
        case Direction::kDownRight:
          sprite_.set_animation(AnimationState::kProjectileDownRight); break;
      }
    }
}

void Projectile::move() {
  switch (direction_){
    case Direction::kUp:
      position_.y -= speed_;
      break;
    case Direction::kDown:
      position_.y += speed_;
      break;
    case Direction::kLeft:
      position_.x -= speed_;
      break;
    case Direction::kRight:
      position_.x += speed_;
      break;
    case Direction::kDownLeft:
      position_.x -= speed_;
      position_.y += speed_;
      break;
    case Direction::kDownRight:
      position_.x += speed_;
      position_.y += speed_;
      break;
    case Direction::kUpLeft:
      position_.x -= speed_;
      position_.y -= speed_;
      break;
    case Direction::kUpRight:
      position_.x += speed_;
      position_.y -= speed_;
      break;
  }
}

void Projectile::destruct(){
  collided_ = true;
  sprite_.set_animation(AnimationState::kProjectileDestroyed);
}

void Projectile::update(World& world){

  if(collided_){
    sprite_.update();
    if(sprite_.ended_){
      destroyed_ = true;
    }
    return;
  }

  move();
  sprite_.update();
}