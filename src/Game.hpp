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

  bool running_;
  Renderer renderer_;
  World world_;

  SDL_Event event_;

  void handle_events();

  void load_level(int level_id);

  void render();

  // Helper methods for initialization
  Renderer init_renderer();

};