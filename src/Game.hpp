#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GameManager.hpp"
#include "IObserver.hpp"
#include "GameManager.hpp"
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

  bool open_ {true};
  
  Renderer renderer_;
  Subject subject_;

  std::vector<double> frame_times_;

  // Observers
  std::shared_ptr<UIManager> ui_manager_;
  std::shared_ptr<SoundManager> sound_manager_;
  std::shared_ptr<GameManager> game_manager_;
  
  SDL_Event event_;

  void handle_game_events(World& world);
  void handle_menu_events();

  void load_level(World& world);

  template <typename T>
  void render_container(const T& container) const;
  
  void render(World& world);
  void render_title() const;

  void run_game();
  void notify(GameEvent event);

  // Helper methods for initialization
  Renderer init_renderer();

};