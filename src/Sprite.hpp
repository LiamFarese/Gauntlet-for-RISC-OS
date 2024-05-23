#pragma once

#include <vector>
#include <array>

#include <SDL/SDL.h>

#include "Models.hpp"

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