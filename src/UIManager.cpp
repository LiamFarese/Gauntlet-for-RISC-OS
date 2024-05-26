#include "UIManager.hpp"

// Configure the player's class and associated attributes
void UIManager::configure_player_class(PlayerClass player_class) {
  player_class_ = player_class;
  switch (player_class) {
    case PlayerClass::kWarrior:
    case PlayerClass::kValkyrie:
      damage_per_hit_ = 3;
      health_ = 500;
      break;
    case PlayerClass::kWizard:
      damage_per_hit_ = 8;
      health_ = 500;
      break;
    case PlayerClass::kElf:
      damage_per_hit_ = 10;
      health_ = 500;
      break;
  }
}

void UIManager::on_notify(GameEvent event){
  switch (event) {
    case GameEvent::kPlayerDamage:
      update_health(-damage_per_hit_); 
      break;
    case GameEvent::kPlayerTickDamage:
      update_health(-1); 
      break;
    case GameEvent::kPlayerFire:
      // No case
      break;
    case GameEvent::kEnemyDestroyed:
      update_score(20); 
      break;
    case GameEvent::kPointPickup:
      update_score(100); 
      break;
    case GameEvent::kHealthPickup:
      update_health(100); 
      break;
    case GameEvent::kHealthPotionPickup: 
      // TODO: implement potions
      break;
    case GameEvent::kDestroyPotionPickup:
      // TODO: implement potions 
      break;
    case GameEvent::kKeyPickup:
      keys_++;
      break;
    case GameEvent::kMenu:
      game_running = false; 
      break;
    case GameEvent::kGame:
      reset_player_stats();
      game_running = true;
      break;
    case GameEvent::kLevelExit:
      // No action
      break;
    case GameEvent::KGameEnd:
      reset_player_stats();
      game_running = false;
      level_name_ = "";
      break;
    case GameEvent::kPlayerDeath:
      game_running = false;
      reset_player_stats();
      break;
    case GameEvent::kQuit:
      break;
    case GameEvent::kOpenDoor:
      keys_--;
      break;
    }
}