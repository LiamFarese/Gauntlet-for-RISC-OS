#pragma once

#include <vector>
#include <array>

#include <SDL/SDL.h>

// Array of animations is indexed using the number value of this enum
enum class AnimationState {
  kMovingUp,
  kMovingUpRight,
  kMovingRight,
  kMovingDownRight,
  kMovingDown,
  kMovingDownLeft,
  kMovingLeft,
  kMovingUpLeft,
  kIdleUp,
  kIdleUpRight,
  kIdleRight,
  kIdleDownRight,
  kIdleDown,
  kIdleDownLeft,
  kIdleLeft,
  kIdleUpLeft,
  kAxe,
  kProjectileUp,
  kProjectileUpRight,
  kProjectileRight,
  kProjectileDownRight,
  kProjectileDown,
  kProjectileDownLeft,
  kProjectileLeft,
  kProjectileUpLeft,
  kProjectileDestroyed,
  kDeath,
};

// Number values represent index on the sprite sheet
enum class SpriteClass : Sint16 {
  kWarrior = 0,
  kValkyrie = 32,
  kWizard = 64,
  kElf = 96,
  kGhost = 128,
  kDemon = 160,
  kBoxer = 192,
  kDarkWizard = 224,
  kBlueGhost = 256
};

class Sprite {

public:

  Sprite() = default;
  Sprite(SpriteClass sprite_class);

  void set_animation(AnimationState state);
  void set_sprite_class(SpriteClass sprite);
  void update(); // To be called each frame to update animation
  SDL_Rect get_frame() const; // Render the current frame

  SpriteClass sprite_class_ {};
  bool ended_ {false};

private:

  using AnimationFrames = std::vector<std::vector<Sint16>>;
  static const AnimationFrames animations_;

  const std::vector<Sint16>* current_frames_ = nullptr; // Pointer to the current animation vector
  size_t current_frame_ {0}; // Index of the current frame in the current animation
  AnimationState current_state_;
  Uint32 last_frame_time_ {0};

};