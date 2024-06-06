#pragma once

#include <SDL/SDL.h>

#include "IObject.hpp"
#include "Sprite.hpp"
#include "Models.hpp"

class World;

class Projectile : public IObject {

public:

  Projectile(SDL_Rect location_, Direction direction, SpriteClass sprite_class, int id);

  virtual void update(World& world) override;
  void destruct();

  // Component
  Sprite sprite_;

  // Projectile properties
  SDL_Rect position_;
  Direction direction_;
  bool collided_;
  bool destroyed_;
  int id_;

  // Compatibility for collision detection
  inline SDL_Rect get_position() const noexcept;

  // Sprite Wrapper
  inline SDL_Rect get_frame() const noexcept;

private:

  static constexpr int speed_ {8};
  void move();

};

inline SDL_Rect Projectile::get_position() const noexcept {
  return position_;
}

inline SDL_Rect Projectile::get_frame() const noexcept {
  return sprite_.get_frame();
}
