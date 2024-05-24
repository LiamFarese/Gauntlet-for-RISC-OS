#pragma once

#include <vector>

#include <SDL/SDL.h>

struct Door {
  SDL_Rect sprite;
  std::vector<SDL_Rect> Location;
};