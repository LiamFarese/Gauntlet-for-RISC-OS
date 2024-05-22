#pragma once
#include <SDL/SDL.h>

#include "Projectile.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"

class World;

class Actor {

public:

  Actor();
  Actor(SpriteClass sprite_class);
  virtual ~Actor() = default;

  virtual void set_position(Sint16 x, Sint16 y) noexcept;
  virtual void update(World& world) = 0;

  bool move_up_    {false};
  bool move_down_  {false};
  bool move_left_  {false};
  bool move_right_ {false};
  bool firing_     {false};
  bool dying_      {false};
  bool dead_       {false};

  Sprite sprite_;
  SDL_Rect position_;
  SDL_Rect last_position_;

  Vector2  velocity_ {0,0};
  AnimationState last_state_ {AnimationState::kIdleDown};
  
  // Keeps track of when the actor last fired
  Uint32 last_fire_;

  // Actor specific
  Uint32 fire_rate_ {350};
  int movespeed_    {0};

  // Direction the actor is facing for projectile 
  Direction direction_;

protected:

 virtual void set_firing_animation() noexcept;
};