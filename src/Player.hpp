#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "Actor.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"

enum class PlayerClass{
  kWarrior,
  kValkyrie,
  kWizard,
  kArcher
};

class Player : public Actor {
    
public:

  Player();
    
  void handle_inputs(const SDL_Event& event);
  void select_player_class(PlayerClass player_class) noexcept;
  // Projectile emit_projectile() override;
  void update();

private:
  static void init_animations(Sprite& sprite);
  PlayerClass player_class_;
};