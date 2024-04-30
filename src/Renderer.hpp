#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <sstream>

#include "Level.hpp"
#include "Projectile.hpp"
#include "Actor.hpp"

class Renderer {

public:

  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen);
  ~Renderer();

  void clear();
  void render(const Actor& actor);
  void render(const Projectile& projectile);
  void render_map();
  void render_text(std::stringstream& message_string, SDL_Rect location);
  void render_frame();

  SDL_Surface* level_background_;

private:

  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
  TTF_Font* font_;
  SDL_Color text_color_ { 255, 255, 255 };
  Uint32 screen_clear_color_ = SDL_MapRGB(screen_->format, 0, 0, 0);

  bool is_zero(SDL_Rect& sprite);
};