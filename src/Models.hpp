#pragma once 
#include "SDL/SDL.h"

// Represents observer events
enum class GameEvent {
  kPlayerDamage,
  kPlayerTickDamage,
  kPlayerFire,
  kEnemyDestroyed,
  kPointPickup,
  kHealthPickup,
  kHealthPotionPickup,
  kDestroyPotionPickup,
  kKeyPickup,
  kMenu,
  kGame,
  kLevelExit
};

// Enum to define different player classes
enum class PlayerClass {
  kWarrior,
  kValkyrie,
  kWizard,
  kElf
};

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

// Direction of entities
enum class Direction {
  kUp,
  kDown,
  kLeft,
  kRight,
  kUpRight,
  kUpLeft,
  kDownLeft,
  kDownRight
};
