#pragma once

#include <SDL/SDL.h>

#include "Sprite.hpp"

enum class Weapon{
  kAxe,
  kSword,
  kFireBall,
  kArrow,
  kDarkFireBall
};

class Projectile{

public:
  Projectile();
  void update();
  void render();

private:
  Sprite sprite_;
  SDL_Rect location_;
  SDL_Rect direction_;
  int damage_;
};