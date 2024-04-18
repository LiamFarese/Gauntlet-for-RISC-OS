#pragma once

#include <unordered_map>
#include <vector>
#include <functional> // For std::hash

#include <SDL/SDL.h>

using SpriteIndex = Sint16;

enum class AnimationState {
  kMovingLeft,
  kMovingRight,
  kMovingUp,
  kMovingDown,
  kMovingUpLeft,
  kMovingDownLeft,
  kMovingUpRight,
  kMovingDownRight,
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

// Number values represent index on the sprite sheet
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


// In c++11 enums cannot be used as hash keys so this hash funtion is needed
namespace std {
  template<> struct hash<AnimationState> {
    size_t operator()(const AnimationState& state) const noexcept {
      return std::hash<int>()(static_cast<int>(state));
    }
  };
}

class Sprite {

public:

  Sprite() = default;
  Sprite(SpriteClass sprite_class);

  void add_animation(AnimationState state, std::vector<SpriteIndex> frames);
  void set_animation(AnimationState state);
  void update(); // To be called each frame to update animation
  SDL_Rect get_frame() const; // Render the current frame

  SpriteClass sprite_class_;


private:

  std::unordered_map<AnimationState, std::vector<SpriteIndex>> animations_;
  std::vector<SpriteIndex>* current_frames_ = nullptr; // Pointer to the current animation vector
  size_t current_frame_ = 0; // Index of the current frame in the current animation
  AnimationState current_state_;
  Uint32 last_frame_time_ = 0;

};