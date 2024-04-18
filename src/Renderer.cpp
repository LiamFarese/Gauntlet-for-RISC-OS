#include "Renderer.hpp"
#include "Projectile.hpp"

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen)
  :sprite_sheet_(sprite_sheet), screen_(screen){
};


void Renderer::render(const Actor& actor){
  SDL_Rect sprite = actor.get_frame();
  if(!isEqualToZeroRect(sprite)) {
    SDL_Rect position = actor.position_;
    SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
  }
}

void Renderer::render(const Projectile& projectile){
  SDL_Rect sprite = projectile.sprite_.get_frame();
  if(!isEqualToZeroRect(sprite)) {
    sprite.h = 32; sprite.w = 32;
    SDL_Rect position = projectile.position_;
    SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
  }
  sprite.h = 32; sprite.w = 32; sprite.x = 800;
  SDL_Rect position = projectile.position_;
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

bool Renderer::isEqualToZeroRect(const SDL_Rect& rect) {
  return rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0;
}