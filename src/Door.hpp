#pragma once

#include <vector>

#include <SDL/SDL.h>

// Vertical door = {352, 288, 32, 32}
// Horizontal door = {320, 288, 32, 32}
struct Door {
  SDL_Rect sprite;
  std::vector<SDL_Rect> location;

  // Constructor to initialize sprite and optionally Location
  Door(SDL_Rect spriteRect, std::vector<SDL_Rect> locs = {})
    : sprite(spriteRect), location(locs) {}
};