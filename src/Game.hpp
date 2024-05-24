#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "IObserver.hpp"
#include "LevelManager.hpp"
#include "Models.hpp"
#include "Subject.hpp"
#include "UIManager.hpp"
#include "SoundManager.hpp"
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
  Subject subject_;

  // Observers
  std::shared_ptr<UIManager> ui_manager_;
  std::shared_ptr<SoundManager> sound_manager_;
  std::shared_ptr<LevelManager> level_manager_;
  
  SDL_Event event_;

  void handle_game_events(World& world);
  void handle_menu_events();

  void load_level(World& world);

  void render(World& world);
  void render_title();

  void run_game();
  void notify(GameEvent event);

  // Helper methods for initialization
  Renderer init_renderer();

};