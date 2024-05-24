#pragma once

#include <future>
#include <memory>
#include <vector>
#include <SDL/SDL.h>

#include "Actor.hpp"
#include "IObserver.hpp"
#include "Models.hpp"
#include "Pickup.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"
#include "Subject.hpp"

class World;
class SoundManager;
class UIManager;

class Player {

public:

  Player(PlayerClass player_class);

  // Method to handle user inputs
  void handle_inputs(const SDL_Event& event);

  // Method to update player state
  void update(World& world);

  // Method to apply damage to the player
  void damage();

  // Method to handle item pickup
  void pickup_item(Pickup pickup);

  inline bool open_door() noexcept;

  // Actor wrapper
  inline void set_position(Sint16 x, Sint16 y) noexcept;
  inline void set_position(SDL_Rect rect) noexcept;
  inline SDL_Rect get_position() const noexcept;
  inline SDL_Rect get_last_position() const noexcept;
  inline void set_last_state(const AnimationState& state) noexcept;

  // Sprite wrapper
  inline SDL_Rect get_frame() const noexcept;

  // Subject wrapper
  inline void addObserver(std::shared_ptr<IObserver> observer);
  inline void notify(GameEvent event);

private:

  // Components
  Subject subject_;
  Actor   actor_;
  Sprite sprite_;

  // Player attributes
  PlayerClass player_class_;  // The class/type of the player
  int damage_per_hit;         // Damage taken per hit

  // Player state
  int score_;                 // Player's score
  int health_;                // Player's health
  int keys_;                  // Number of keys the player has

  Uint32 health_timer_;       // Timer for health-related events

  // Private method to move the player
  void move(int pixels);
  void fire(World& world);

  // Private method to handle health ticking
  void tick_health();

  // helper function to initalise stats
  void init_stats();
};

inline bool Player::open_door() noexcept{
  if(keys_ > 0){
    keys_--;
    return true;
  }
  return false;
}

// Actor wrapper 
inline void Player::set_position(Sint16 x, Sint16 y) noexcept {
  actor_.set_position(x, y);
}

inline void Player::set_position(SDL_Rect rect) noexcept {
  actor_.position_ = rect;
}

inline SDL_Rect Player::get_position() const noexcept {
  return actor_.position_;
}

inline SDL_Rect Player::get_last_position() const noexcept {
  return actor_.last_position_;
}

inline void Player::set_last_state(const AnimationState& state) noexcept {
  actor_.last_state_ = state;
}

// Sprite Wrapper
inline SDL_Rect Player::get_frame() const noexcept {
  return sprite_.get_frame();
}

// Subject wrapper
inline void Player::notify(GameEvent event){
  subject_.notify(event);
}

inline void Player::addObserver(std::shared_ptr<IObserver> observer) {
  subject_.addObserver(observer);
}