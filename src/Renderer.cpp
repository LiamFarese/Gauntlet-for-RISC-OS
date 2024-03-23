#include "Renderer.hpp"

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen)
  :sprite_sheet_(sprite_sheet), screen_(screen){
};

void Renderer::render(const Actor& actor){
  SDL_Rect position = actor.get_position();
  SDL_Rect sprite   = actor.get_frame();
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}