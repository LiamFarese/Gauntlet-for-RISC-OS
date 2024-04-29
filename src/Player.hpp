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
  kElf
};

class Player : public Actor {
    
public:

  Player();

  void handle_inputs(const SDL_Event& event);
  void select_player_class(PlayerClass player_class) noexcept;
  void update(World& world) override;

private:

  PlayerClass player_class_;

  void move(int pixels);
  void set_firing_animation(Direction direction);
};