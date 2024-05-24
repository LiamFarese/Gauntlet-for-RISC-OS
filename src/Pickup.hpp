#pragma once

#include <SDL/SDL.h>

#include "Actor.hpp"

enum class PickupType {
  kPoints,
  kHealth,
  kHealthPotion,
  kDestroyPotion,
  kKey, 
  kExit
};

class Pickup {

public:

  Pickup(PickupType Pickup, SDL_Rect position)
    : pickup_type_(Pickup), position_(position) {
      switch (Pickup) {
        case PickupType::kPoints:
          sprite_ = {224, 288, 32, 32}; break;
        case PickupType::kHealth:
          sprite_ = {96, 288, 32, 32}; break;
        case PickupType::kHealthPotion:
          sprite_ = {192, 288, 32, 32}; break;
        case PickupType::kDestroyPotion:
          sprite_ = {32, 288, 32, 32}; break;
        case PickupType::kKey:
          sprite_ = {160, 288, 32, 32}; break;
          break;
        case PickupType::kExit:
          sprite_ = {384, 288, 0, 0}; break;
          break;
        }
  }

  PickupType pickup_type_;

  // For rendering and Collision compatibility
  inline SDL_Rect get_position() const noexcept;
  inline SDL_Rect get_frame() const noexcept;

private:

  SDL_Rect position_;
  SDL_Rect sprite_;


};

inline SDL_Rect Pickup::get_position() const noexcept {
  return position_;
}

inline SDL_Rect Pickup::get_frame() const noexcept {
  return sprite_;
}