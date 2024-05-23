#pragma once

#include <vector>
#include <SDL/SDL.h>

#include "Actor.hpp"
#include "Models.hpp"
#include "Pickup.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"

class World;
class SoundManager;
class UIManager;

class Player : public Actor {

public:
  Player(PlayerClass player_class, UIManager& ui_manager, SoundManager& sound_manager);

  // Method to handle user inputs
  void handle_inputs(const SDL_Event& event);

  // Method to update player state, override from Actor
  void update(World& world) override;

  // Method to apply damage to the player
  void damage();

  // Method to handle item pickup
  void pickup_item(Pickup pickup);
  void notify(GameEvent event);


private:
  // Player attributes
  PlayerClass player_class_;  // The class/type of the player
  UIManager& ui_manager_;     // Reference to the UI manager
  int damage_per_hit;         // Damage taken per hit

  // Player state
  int score_;                 // Player's score
  int health_;                // Player's health

  Uint32 health_timer_;       // Timer for health-related events

  // Private method to move the player
  void move(int pixels);
  void fire(World& world);

  // Private method to handle health ticking
  void tick_health();

  // Temporary
  SoundManager& sound_manager_;
};