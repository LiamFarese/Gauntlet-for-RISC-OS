#pragma once

#include "IObserver.hpp"
#include "Models.hpp"
#include "World.hpp"

class GameManager : public IObserver {

public:

  GameManager();
  void on_notify(GameEvent event);
  std::string load_level(World& world, UIManager& ui_manager_);

  bool level_exited;
  int level_id;
  bool running_;
  bool title_screen_;

};