#pragma once

#include <SDL/SDL.h>

#include "Sprite.hpp"

class Character {

public:

  Character(SDL_Surface* spriteSheet, SDL_Surface* screen);

  virtual void update() = 0;
  virtual void setPosition(int x, int y);
  virtual void render();

protected:

  SDL_Surface* m_screen;
  SDL_Rect m_position;
  Sprite m_sprite;
  AnimationState m_direction;
  
  bool m_moveUp;
  bool m_moveDown;
  bool m_moveLeft;
  bool m_moveRight;

};