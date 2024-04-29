#include "Renderer.hpp"
#include "Map.hpp"
#include "Projectile.hpp"
#include "SDL/SDL_video.h"

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* background, SDL_Surface* screen)
  :sprite_sheet_(sprite_sheet), background_(background), screen_(screen){
};

void Renderer::render(const Actor& actor){
  SDL_Rect sprite = actor.sprite_.get_frame();
  // if(!is_zero(sprite)) {
    SDL_Rect position = actor.position_;
    SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
  // }
}

void Renderer::render(const Projectile& projectile){
  SDL_Rect sprite = projectile.sprite_.get_frame();
  if(!is_zero(sprite)) {
    sprite.h = 32; sprite.w = 32;
    SDL_Rect position = projectile.position_;
    SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
  }
  sprite.h = 32; sprite.w = 32; sprite.x = 800;
  SDL_Rect position = projectile.position_;
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

void Renderer::render(const Map& map) {
  SDL_Rect sprite {0,0,32,32};
  SDL_Rect position = {0,0,32,32};
  for(auto& row  : map.tile_map){
    for(auto& tile : row){
      SDL_Rect sprite = tile.sprite;
      SDL_Rect position = tile.position;
      SDL_BlitSurface(background_, &sprite, screen_, &position);
    }
  }
}

bool Renderer::is_zero(const SDL_Rect& rect) {
  return rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0;
}