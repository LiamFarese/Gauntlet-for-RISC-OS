#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "Character.hpp"
#include "Sprite.hpp"

enum class PlayerClass{
  Warrior,
  Valkyrie,
  Wizard,
  Archer
};

class Player : public Character {
    
public:

  Player(SDL_Surface* spriteSheet, SDL_Surface* screen);
    
  void handleInputs(const SDL_Event& event);
  void selectPlayerClass(PlayerClass playerClass);
  void update() override;

private:
  static void initAnimations(Sprite& sprite);
  PlayerClass m_playerClass;
};