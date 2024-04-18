#pragma once

#include "Projectile.hpp"
#include "SDL/SDL.h"

#include "Actor.hpp"

class Renderer {

public:

  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen);

  void render(const Actor& actor);
  void render(const Projectile& projectile);

private:
  bool isEqualToZeroRect(const SDL_Rect& rect);
  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
};