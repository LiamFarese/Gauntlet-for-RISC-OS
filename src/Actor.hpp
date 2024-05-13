#pragma once

#include "Projectile.hpp"
#include <SDL/SDL.h>


class World;

#include "Sprite.hpp"

class Actor {

public:

  Actor();
  virtual ~Actor() = default;

  virtual void set_position(Sint16 x, Sint16 y) noexcept;
  virtual void update(World& world) = 0;

  bool move_up_;
  bool move_down_;
  bool move_left_;
  bool move_right_;
  bool firing_;
  bool dying_;
  bool dead_;

  Uint32 fire_rate_ {100};
  Uint32 last_fire_ {0};

  SDL_Rect position_;
  SDL_Rect last_position_;
  AnimationState last_state_;

  Sprite sprite_;
  Direction direction_;  
};