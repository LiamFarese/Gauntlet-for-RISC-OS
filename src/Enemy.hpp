#pragma once

#include <random>

#include "Actor.hpp"
#include "Player.hpp"
#include "Projectile.hpp"

enum class EnemyClass{
  kGhost,
  kDemon,
  kDarkWizard,
  kBlueGhost
};

class Enemy: public Actor {

public:

  Enemy(EnemyClass enemy_class);

  void update(const Player& player);
  void set_enemy_class(EnemyClass enemy_class) noexcept;
  // Projectile emit_projectile() override;

private:

  EnemyClass enemy_class_;
  bool thinking;
  std::mt19937 engine{std::random_device{}()};
  std::uniform_int_distribution<int> dist{1,4};
};