#include "GameManager.hpp"
#include "Models.hpp"
#include <iostream>

GameManager::GameManager(): level_exited(false), level_id(0), running_(false), title_screen_(true) {}

std::string GameManager::load_level(World& world, UIManager& ui_manager_){
  std::string level_name {};
  switch(level_id){
    case (0):
      world.load_level(0); 
      level_name = world.level_name_;
      ui_manager_.level_name_ = "Training 1";
      break;
    case (1):
      world.load_level(1); 
      level_name = world.level_name_;
      ui_manager_.level_name_ = "Training 2";
      break;
    case (2):
      world.load_level(2);
      level_name = world.level_name_;
      ui_manager_.level_name_ = "Training 3";
      break;
    default:
      level_name = "ended";
      break;
  }
  return level_name;
}

void GameManager::on_notify(GameEvent event){
  switch (event) {
    case GameEvent::kMenu:
      running_ = false;
      title_screen_ = true;
      break;
    case GameEvent::kGame:
      running_ = true;
      title_screen_ = false;
      break;
    case GameEvent::kLevelExit:
      level_exited = true;
      level_id++;
      break;
    case GameEvent::KGameEnd:
      running_ = false;
      title_screen_ = true;
      level_id = 0;
      break;
    case GameEvent::kPlayerDeath:
      running_ = false;
      title_screen_ = true;
      break;
    case GameEvent::kQuit:
      running_ = false;
      title_screen_ = false;
      break;
    case GameEvent::kHealthPotionPickup:
      // No action
      break;
    default:
      break;
  }
}