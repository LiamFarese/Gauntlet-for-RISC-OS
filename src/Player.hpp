#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "Actor.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"

class World;
class UIManager;

enum class PlayerClass {
  kWarrior,
  kValkyrie,
  kWizard,
  kElf
};

class Player : public Actor {
    
public:

  Player(PlayerClass player_class, UIManager& ui_manager);

  void handle_inputs(const SDL_Event& event);
  void select_player_class(PlayerClass player_class) noexcept;
  void update(World& world) override;

  void damage();
  void damage(int hp);
  void increment_score(const int points);

private:

  PlayerClass player_class_;
  UIManager& ui_manager_;
  int damage_per_hit;

  int score_;
  int health_;

  Uint32 health_timer_;
  void move(int pixels);
};