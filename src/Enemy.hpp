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


class Enemy {

public:

  Enemy(EnemyClass enemy_class, SDL_Rect position);

  void update(World& world);
  void death();

  int id_;
  static int ID;

  // Actor Wrapper
  inline SDL_Rect get_position() const noexcept;
  inline void set_position(SDL_Rect rect) noexcept;
  inline SDL_Rect get_last_position() const noexcept;
  inline bool is_dying() const noexcept;
  inline bool is_dead() const noexcept;

  // Sprite Wrapper
  inline SDL_Rect get_frame() const noexcept;

private:

  // Components
  Actor   actor_;
  Sprite sprite_;

  // Enemy state
  EnemyClass enemy_class_;
  bool blocked_ {false};
  Uint32 last_stuck_attempt_ {0};

  int standing_timer_;
  static constexpr int standing_duration_ {8};

  // Move functions
  void move(int pixels, World& world);
  bool try_move(World& world, Sint16 vel_x, Sint16 vel_y);
  void move_around_tiles(World& world, Sint16 dy, Sint16 dx);
  void set_moving_animation();

  bool check_collisions(Enemy& a, Enemy& b, Sint16 dx, Sint16 dy);

};

// Wrapper around actor
inline SDL_Rect Enemy::get_position() const noexcept {
  return actor_.position_;
}

inline void Enemy::set_position(SDL_Rect rect) noexcept {
  actor_.position_ = rect;
}

inline SDL_Rect Enemy::get_last_position() const noexcept {
  return actor_.last_position_;
}

inline SDL_Rect Enemy::get_frame() const noexcept {
  return sprite_.get_frame();
}

inline bool Enemy::is_dying() const noexcept {
  return actor_.dying_;
}

inline bool Enemy::is_dead() const noexcept {
  return actor_.dead_;
}

