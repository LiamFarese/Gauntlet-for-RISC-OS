#pragma once

#include "Character.hpp"
#include "Player.hpp"
#include "Projectile.hpp"

enum class EnemyClass{
  kGhost,
  kDemon,
  kDarkWizard,
  kBlueGhost
};

class Enemy: public Character {

public:

  Enemy(SDL_Surface* spriteSheet, SDL_Surface* screen);

  void update(const Player& player);
  void set_enemy_class(EnemyClass enemy_class) noexcept;
  Projectile emit_projectile() override;

private:

  EnemyClass enemy_class_;
};