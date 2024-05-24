#include "LevelManager.hpp"

LevelManager::LevelManager(): level_exited(false), level_id(0) {}

std::string LevelManager::load_level(World& world, UIManager& ui_manager_){
  std::string level_name {};
  switch(level_id){
    case (0):
      world.load_level(0); 
      level_name = world.map_.level_name;
      ui_manager_.level_name_ = "Training 1";
      break;
    case (1):
      world.load_level(0); 
      level_name = world.map_.level_name;
      ui_manager_.level_name_ = "Training 2";
      break;
  }
  return level_name;
}

void LevelManager::on_notify(GameEvent event){
  if(event == GameEvent::kLevelExit){
    level_exited = true;
  }
}