#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "UIManager.hpp"
#include "World.hpp"
#include "Renderer.hpp"

class Game {

public:

  Game();

  ~Game();

  void start();

private:

  bool open_         {true};
  bool title_screen_ {false};
  bool running_      {false};
  
  Renderer renderer_;
  UIManager ui_manager_;
  
  SDL_Event event_;

  void handle_game_events(World& world);
  void handle_menu_events();

  void load_level(World& world, int level_id);

  void render(World& world);
  void render_title();

  void run_game();

  // Helper methods for initialization
  Renderer init_renderer();

};