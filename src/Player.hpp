#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "Character.hpp"
#include "Sprite.hpp"

enum class PlayerClass{
  kWarrior,
  kValkyrie,
  kWizard,
  kArcher
};

class Player : public Character {
    
public:

  Player(SDL_Surface* spriteSheet, SDL_Surface* screen);
    
  void handle_inputs(const SDL_Event& event);
  void select_player_class(PlayerClass player_class);
  void update() override;

private:
  static void init_animations(Sprite& sprite);
  PlayerClass player_class_;
};