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
#include "UIManager.hpp"

// Renderer class responsible for all rendering operations
class Renderer {

public:
  // Constructors and destructor
  Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen, SDL_Surface* logo);
  Renderer();
  ~Renderer();

  // Resource destruction method
  void destroy();

  // Public methods for rendering various game elements
  void clear();
  void render(const Actor& actor) const;
  void render(const Projectile& projectile) const;
  void render(const Pickup& pickup) const;
  void render_map(const Player& player);
  void render_title() const;
  void render_sidebar(UIManager& ui_manager);
  void render_class_text(const std::stringstream& message_string, SDL_Rect location, SDL_Color color);
  void render_text(const std::string& message_string, SDL_Rect location);
  void render_frame() const;

  // Public attributes for SDL surfaces and rendering settings
  SDL_Surface* level_background_;
  SDL_Rect camera_ {0, 0, 960, 640};


private:
  // Private attributes
  SDL_Surface* sprite_sheet_;
  SDL_Surface* screen_;
  SDL_Surface* title_screen_;
  SDL_Surface* logo_;

  TTF_Font* font_;
  TTF_Font* title_font_;
  SDL_Color text_color_ { 255, 255, 255 };
  Uint32 screen_clear_color_;

  // Private helper methods
  void render_static_ui();
  bool is_zero(SDL_Rect& sprite) const;
  bool clip(SDL_Rect& location) const;
};
