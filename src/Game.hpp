#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "World.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

class Game {

public:

  Game();

  ~Game();

  void run();

private:
  SDL_Surface* screen_;
  SDL_Surface* sprite_sheet_;
  Renderer renderer;
  World world_;

  Uint32 screen_clear_color_;
  SDL_Color text_color_ { 255, 255, 255 };
  TTF_Font* font_;
  
  bool running_;
  SDL_Event event_;

  void handle_events();

  void display_text(std::stringstream& message_string, SDL_Rect location);

  void render();

  // Helper methods for initialization
  SDL_Surface* init_screen();
  SDL_Surface* init_sprite_sheet();

};