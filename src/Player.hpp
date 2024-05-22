#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "Actor.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"

enum class PlayerClass {
  kWarrior,
  kValkyrie,
  kWizard,
  kElf
};

#include "World.hpp"

class Player : public Actor {
    
public:

  Player();
  Player(PlayerClass player_class);

  void handle_inputs(const SDL_Event& event);
  void select_player_class(PlayerClass player_class) noexcept;
  void update(World& world) override;
  int health_ {500};

  void damage();
  void increment_score(const int points);
private:

  PlayerClass player_class_;
  int damage_per_hit;

  // int health_ {500};
  int score_ {0};

  Uint32 timer_ {0};
  void move(int pixels);
};