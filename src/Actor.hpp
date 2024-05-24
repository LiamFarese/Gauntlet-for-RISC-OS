#pragma once
#include <SDL/SDL.h>

#include "Projectile.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"

class World;

class Actor {

public:

  Actor();

  void set_position(Sint16 x, Sint16 y) noexcept;

  bool move_up_    {false};
  bool move_down_  {false};
  bool move_left_  {false};
  bool move_right_ {false};
  bool firing_     {false};
  bool dying_      {false};
  bool dead_       {false};

  SDL_Rect position_;
  SDL_Rect last_position_;
  // Direction the actor is facing 
  Direction direction_;

  Vector2  velocity_;
  AnimationState last_state_;
  
  // Keeps track of when the actor last fired
  Uint32 last_fire_;

  // Actor specific
  Uint32 fire_rate_ {275};
  int movespeed_    {0};

};