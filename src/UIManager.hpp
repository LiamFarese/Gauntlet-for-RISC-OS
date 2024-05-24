#pragma once

#include "IObserver.hpp"

#include <string>
#include <sstream>

#include "Player.hpp"

class UIManager : public IObserver {

public:
  // Constructor
  UIManager()
    : health_str_("000"), score_str_("000"), game_running(false),
      health_(0), score_(0), damage_per_hit_(0), health_potions_(0), keys_(0) {}

  // Used for rendering the health, score and level name to the sidebar
  std::string health_str_;
  std::string score_str_;
  std::string level_name_;

  // UI is rendered differently depending on if the game is running or not
  bool game_running;

  void configure_player_class(PlayerClass player_class);

  void on_notify(GameEvent event);

  PlayerClass player_class_;

private:
  void reset_player_stats();
  void update_health(int new_health);
  void update_score(int new_score);

  int health_;
  int score_;
  int damage_per_hit_;

  // Represents the number of keys and potions the player has
  int health_potions_;
  int keys_;

  // Buffer used to convert health and score to strings to display
  std::stringstream buff_;
};

// Ensure that player stats are reset after reselecting in title screen
inline void UIManager::reset_player_stats(){
  score_          = 0;
  health_         = 500;
  health_potions_ = 0;
  keys_           = 0;
  health_str_     = "000";
  score_str_      = "000";
}

// Update the player's health and its string representation
inline void UIManager::update_health(int health) {
  health_ += health ;
  buff_.str(std::string());
  buff_.clear();
  buff_ << health_;
  health_str_ = buff_.str();
}

// Update the player's score and its string representation
inline void UIManager::update_score(int points) {
  score_ += points;
  buff_.str(std::string());
  buff_.clear();
  buff_ << score_;
  score_str_ = buff_.str();
}
