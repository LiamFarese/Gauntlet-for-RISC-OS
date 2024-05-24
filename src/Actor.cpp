#include "Actor.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"

Actor::Actor()
: position_({0,0,32,32}), last_position_({1,1,32,32}), 
  velocity_({0,0}), last_fire_(0) {
  
}

void Actor::set_position(Sint16 x, Sint16 y) noexcept {
  position_.x = x;
  position_.y = y;
}
