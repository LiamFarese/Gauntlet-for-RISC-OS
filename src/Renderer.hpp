#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <string>

#include "Level.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Actor.hpp"
#include "SDL/SDL_video.h"

class Renderer {

public:

  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen);
  Renderer();
  ~Renderer();

  void clear();
  void render(const Actor& actor) const;
  void render(const Projectile& projectile) const;
  void render_map(const Player& player);
  void render_title() const;
  void render_sidebar();
  void render_text(const std::string& message_string, SDL_Rect location);
  void render_frame() const;

  void destory();

  SDL_Surface* level_background_;

  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
  SDL_Surface* title_screen_;

  SDL_Rect camera_ {0,0,960,640};

  TTF_Font* font_;
  SDL_Color text_color_ { 255, 255, 255 };
  Uint32 screen_clear_color_ = SDL_MapRGB(screen_->format, 0, 0, 0);

private:

  bool is_zero(SDL_Rect& sprite) const;
  bool clip(SDL_Rect& location) const;
};