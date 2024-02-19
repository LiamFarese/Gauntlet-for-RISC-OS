#pragma once

#include <unordered_map>
#include <vector>
#include <functional> // For std::hash

#include <SDL/SDL.h>

using SpriteIndex = Sint16;

enum class AnimationState {
  kRunningLeft,
  kRunningRight,
  kRunningUp,
  kRunningDown,
  kRunningUpLeft,
  kRunningDownLeft,
  kRunningUpRight,
  kRunningDownRight,
  kAttacking,
  kIdleUp,
  kIdleDown,
  kIdleLeft,
  kIdleRight,
  kIdleUpRight,
  kIdleUpLeft,
  kIdleDownRight,
  kIdleDownLeft
};

enum class SpriteClass : Sint16 {
  kWarrior = 0,
  kValkyrie = 32,
  kWizard = 64,
  kArcher = 96,
  kGhost = 128,
  kDemon = 160,
  kDarkWizard = 192,
  kBlueGhost = 224
};

namespace std {
  template<> struct hash<AnimationState> {
    size_t operator()(const AnimationState& state) const noexcept {
      return std::hash<int>()(static_cast<int>(state));
    }
  };
}

class Sprite {

public:

  Sprite(SDL_Surface* spriteSheet);

  void add_animation(AnimationState state, std::vector<SpriteIndex> frames);
  void set_animation(AnimationState state);
  void set_sprite_class(SpriteClass SpriteClass);
  void update(); // To be called each frame to update animation
  void render(SDL_Surface* targetSurface, Sint16 x, Sint16 y); // Render the current frame

private:

  SDL_Surface* sprite_sheet_;
  std::unordered_map<AnimationState, std::vector<SpriteIndex>> animations_;
  std::vector<SpriteIndex>* current_frames_ = nullptr; // Pointer to the current vector of frames
  size_t current_frame_ = 0; // Index of the current frame in the current animation
  AnimationState current_state_;
  Uint32 last_frame_time_ = 0;

  SpriteClass sprite_class_ = SpriteClass::kWarrior;
};