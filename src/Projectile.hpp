#pragma once

#include <SDL/SDL.h>

#include "Sprite.hpp"
#include "Models.hpp"

class World;

class Projectile {

public:

  Projectile(SDL_Rect location_, Direction direction, SpriteClass sprite_class, int id);

  void update(World& world);
  void destruct();

  SDL_Rect position_;
  Direction direction_;
  Sprite sprite_;
  bool collided_;
  bool destroyed_;
  int id_;

private:

  static constexpr int speed_ {15};
  void move();

};