#pragma once

#include <unordered_map>
#include <vector>
#include <functional> // For std::hash

#include <SDL/SDL.h>

using SpriteIndex = Sint16;

enum class AnimationState {
  RunningLeft,
  RunningRight,
  RunningUp,
  RunningDown,
  RunningUpLeft,
  RunningDownLeft,
  RunningUpRight,
  RunningDownRight,
  Jumping,
  Attacking,
  IdleUp,
  IdleDown,
  IdleLeft,
  IdleRight,
  IdleUpRight,
  IdleUpLeft,
  IdleDownRight,
  IdleDownLeft
};

enum class SpriteClass : Sint16 {
  Warrior = 0,
  Valkyrie = 32,
  Wizard = 64,
  Archer = 96,
  Ghost = 128,
  Demon = 160,
  DarkWizard = 192,
  BlueGhost = 224
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

  void addAnimation(AnimationState state, std::vector<SpriteIndex> frames);
  void setAnimation(AnimationState state);
  void setSpriteClass(SpriteClass SpriteClass);
  void update(); // To be called each frame to update animation
  void render(SDL_Surface* targetSurface, int x, int y); // Render the current frame

private:

  SDL_Surface* m_spriteSheet;
  std::unordered_map<AnimationState, std::vector<SpriteIndex>> m_animations;
  std::vector<SpriteIndex>* m_currentFrames = nullptr; // Pointer to the current vector of frames
  size_t m_currentFrame = 0; // Index of the current frame in the current animation
  AnimationState m_currentState;
  Uint32 m_lastFrameTime = 0;

  SpriteClass m_spriteClass;
};