#pragma once

#include <random>

#include "Actor.hpp"
#include "Projectile.hpp"
#include "SDL/SDL_stdinc.h"
#include "Sprite.hpp"

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

  int id_;
  static int ID;

private:

  EnemyClass enemy_class_;
  void move(int pixels, World& world);
  bool try_move(World& world, Sint16 vel_x, Sint16 vel_y);
  void move_around_tiles(World& world, Sint16 dy, Sint16 dx);
  void set_moving_animation();

  bool blocked_ {false};
  Uint32 last_stuck_attempt_ {0};

  int standing_timer_;
  static constexpr int standing_duration_ {8};

  bool check_collisions(Enemy& a, Enemy& b, Sint16 dx, Sint16 dy);

};