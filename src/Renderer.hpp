#pragma once

#include "SDL/SDL.h"

#include "Actor.hpp"

class Renderer {

public:

  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen);

  void render(const Actor& actor);

private:

  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
};