#include "Actor.hpp"

Actor::Actor()
: move_up_(false), move_down_(false), move_left_(false), move_right_(false),
  position_({0,0,32,32}) {
}

void Actor::set_position(Sint16 x, Sint16 y) noexcept{
  position_.x = x;
  position_.y = y;
}

SDL_Rect Actor::get_position() const noexcept{
  return position_;
}

SDL_Rect Actor::get_frame() const {
  return sprite_.get_frame();
}

void Actor::set_last_state(AnimationState state) noexcept{
  last_state_ = state;
}