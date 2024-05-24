#pragma once

#include "IObserver.hpp"
#include "Models.hpp"
#include "World.hpp"

class LevelManager : public IObserver {

public:

  LevelManager();
  void on_notify(GameEvent event);
  std::string load_level(World& world, UIManager& ui_manager_);

  bool level_exited;
  int level_id;
};