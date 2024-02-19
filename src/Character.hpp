#pragma once

#include <SDL/SDL.h>

#include "Sprite.hpp"

class Character {

public:

  Character(SDL_Surface* sprite_sheet, SDL_Surface* screen);

  virtual void update() = 0;
  virtual void set_position(Sint16 x, Sint16 y);
  virtual void render();

protected:

  SDL_Surface* screen_;
  SDL_Rect position_;
  Sprite sprite_;
  AnimationState direction_;
  
  bool move_up_;
  bool move_down_;
  bool move_left_;
  bool move_right_;

};