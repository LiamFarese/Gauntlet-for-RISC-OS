#pragma once

#include <SDL/SDL.h>

#include "Map.hpp"
#include "Projectile.hpp"
#include "Actor.hpp"
#include "SDL/SDL_video.h"

class Renderer {

public:

  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* background, SDL_Surface* screen);

  void render(const Actor& actor);
  void render(const Projectile& projectile);
  void render(const Map& map);

private:

  bool is_zero(const SDL_Rect& rect);
  SDL_Surface* sprite_sheet_;
  SDL_Surface* background_;
  SDL_Surface* screen_;
};