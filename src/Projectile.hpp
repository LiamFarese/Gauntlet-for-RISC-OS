#pragma once

#include <SDL/SDL.h>

#include "Sprite.hpp"


enum class Direction {
  kUp,
  kDown,
  kLeft,
  kRight,
  kUpRight,
  kUpLeft,
  kDownLeft,
  kDownRight
};

class Projectile{

public:
  Projectile(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Rect location_, Direction direction, SpriteClass sprite_class);
  void update();
  void render();

private:
  Sprite sprite_;
  SDL_Surface* screen_;
  SDL_Rect position_;
  Direction direction_;
  SpriteClass weapon_;
};