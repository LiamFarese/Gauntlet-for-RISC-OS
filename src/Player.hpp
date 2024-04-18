#pragma once

#include <vector>

#include <SDL/SDL.h>


#include "Actor.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"
#include "World.hpp"

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
  void update(World& world);

private:

  PlayerClass player_class_;

  static void init_animations(Sprite& sprite);
};