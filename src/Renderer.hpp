#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <sstream>

#include "Level.hpp"
#include "Pickup.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Actor.hpp"
#include "SDL/SDL_video.h"
#include "UIManager.hpp"

// Renderer class responsible for all rendering operations
class Renderer {

public:
  // Constructors and destructor
  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen,
           SDL_Surface* logo, SDL_Surface* key);
  Renderer();
  ~Renderer();

  // Resource destruction method
  void destroy();

  // Public methods for rendering various game elements
  void clear();
  
  // Renders all game entities
  template<typename T>
  void render(const T& t) const;

  void render(const Door& door) const;

  void render_map(const Player& player);
  void render_title() const;
  void render_sidebar(UIManager& ui_manager) const;
  void render_class_text(const std::stringstream& message_string, SDL_Rect location, SDL_Color color) const;
  void render_text(const std::string& message_string, SDL_Rect location) const;
  void render_frame() const;

  void load_new_level(SDL_Surface* level);

  // Public attributes for SDL surfaces and rendering settings
  SDL_Surface* level_background_;
  SDL_Rect camera_ {0, 0, 960, 640};

private:
  // Private attributes
  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
  SDL_Surface* title_screen_;
  SDL_Surface* logo_;
  SDL_Surface* key_;

  TTF_Font* font_;
  TTF_Font* title_font_;
  SDL_Color text_color_ { 255, 255, 255 };
  Uint32 screen_clear_color_ = SDL_MapRGB(screen_->format, 0, 0, 0);

  // Private helper methods
  void render_static_ui() const;
  void render_keys(UIManager& ui_manager, Sint16 y_location) const;
  bool is_zero(SDL_Rect& sprite) const;
  bool clip(SDL_Rect& location) const;
};

template<typename T>
void Renderer::render(const T& t) const {
  SDL_Rect position = t.get_position();

  if (clip(position)) {
    return;
  }

  SDL_Rect sprite = t.get_frame();

  if (is_zero(sprite)) {
    return;
  }

  // Camera offset
  position.x -= camera_.x;
  position.y -= camera_.y;

  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

