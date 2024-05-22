#pragma once

#include "Player.hpp"
#include <string>
#include <sstream>

class UIManager {

public:

  UIManager()
  : health_str("0"), score_str("0"), game_running(false), health_(0), score_(0) {
  };

  std::string health_str;
  std::string score_str;

  PlayerClass player_class_;
  bool game_running;

  void update_health(int new_health);
  void update_score(int new_score);

private:

  int health_;
  int score_;
  std::stringstream buff_;
};

inline void UIManager::update_health(int new_health){
  health_ = new_health;

  buff_.str(std::string());
  buff_.clear();
  buff_ << new_health;
  health_str = buff_.str();
}

inline void UIManager::update_score(int new_score){
  score_ = new_score;

  buff_.str(std::string());
  buff_.clear();
  buff_ << new_score;
  score_str = buff_.str();
}