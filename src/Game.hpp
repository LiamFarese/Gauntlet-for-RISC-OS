#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>


#include "World.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

class Game {

public:

  Game();

  ~Game();

  void run();

private:

  Renderer renderer;
  World world_;
  
  bool running_;
  SDL_Event event_;

  void handle_events();

  void display_text(std::stringstream& message_string, SDL_Rect location);

  void load_level(int level_id);

  void render();

  // Helper methods for initialization
  Renderer init_renderer();

};