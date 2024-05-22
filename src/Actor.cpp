#include "Actor.hpp"
#include "Sprite.hpp"

Actor::Actor()
: position_({0,0,32,32}), last_position_({1,1,32,32}), last_fire_(0) {
}

Actor::Actor(SpriteClass sprite_class)
  :sprite_(sprite_class), position_({0,0,32,32}), last_position_({1,1,32,32}), last_fire_(0) {
}

void Actor::set_position(Sint16 x, Sint16 y) noexcept {
  position_.x = x;
  position_.y = y;
}

void Actor::set_firing_animation() noexcept {
  switch (direction_) {
    case Direction::kUp:
      sprite_.set_animation(AnimationState::kMovingUp); break;
    case Direction::kDown:
      sprite_.set_animation(AnimationState::kMovingDown); break;
    case Direction::kLeft:
      sprite_.set_animation(AnimationState::kMovingLeft); break;
    case Direction::kRight:
      sprite_.set_animation(AnimationState::kMovingRight); break;
    case Direction::kUpRight:
      sprite_.set_animation(AnimationState::kMovingUpRight); break;
    case Direction::kUpLeft:
      sprite_.set_animation(AnimationState::kMovingUpLeft); break;
    case Direction::kDownRight:
      sprite_.set_animation(AnimationState::kMovingDownRight); break;
    case Direction::kDownLeft:
      sprite_.set_animation(AnimationState::kMovingDownLeft); break;
     default:
      break;
  }
}
