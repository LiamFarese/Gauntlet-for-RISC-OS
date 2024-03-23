#pragma once

#include <SDL/SDL.h>


#include "Sprite.hpp"
#include "Projectile.hpp"

class Actor {

public:

  Actor();

  virtual void set_position(Sint16 x, Sint16 y) noexcept;
  virtual SDL_Rect get_position() const noexcept;
  virtual void set_last_state(AnimationState state) noexcept;
  // virtual Projectile emit_projectile() = 0;
  virtual SDL_Rect get_frame() const;


protected:

  SDL_Surface* screen_;
  SDL_Rect position_;
  Sprite sprite_;
  AnimationState last_state_;
  Direction direction_;
  
  bool move_up_;
  bool move_down_;
  bool move_left_;
  bool move_right_;

};