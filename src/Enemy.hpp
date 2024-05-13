#pragma once

#include <random>

#include "Actor.hpp"
#include "Projectile.hpp"

enum class EnemyClass{
  kGhost,
  kDemon,
  kBoxer,
  kDarkWizard,
  kBlueGhost
};

class Enemy: public Actor {

public:

  Enemy(EnemyClass enemy_class, SDL_Rect position);

  void update(World& world) override;
  void death();

private:

  EnemyClass enemy_class_;
  bool thinking;
  std::mt19937 engine{std::random_device{}()};
  std::uniform_int_distribution<int> dist{1,4};
};