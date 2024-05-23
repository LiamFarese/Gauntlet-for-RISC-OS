#include "UIManager.hpp"

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
      // TODO: implement keys
      break;
    case GameEvent::kMenu:
      game_running = false; 
      break;
    case GameEvent::kGame:
      game_running = true;
      break;
    case GameEvent::kLevelExit:
      // TODO: implement next level
      break;
    }
}