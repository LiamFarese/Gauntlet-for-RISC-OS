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

class World;

class Projectile{

public:

  Projectile(SDL_Rect location_, Direction direction, SpriteClass sprite_class);

  void update(World& world);

  SDL_Rect position_;
  Sprite sprite_;

private:

  Direction direction_;
  SpriteClass weapon_;
};