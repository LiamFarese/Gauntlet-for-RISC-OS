#include "Player.hpp"

#include "Models.hpp"
#include "SDL/SDL_video.h"
#include "SoundManager.hpp"
#include "UIManager.hpp"
#include "World.hpp"

Player::Player(PlayerClass player_class) 
  : player_class_(player_class), score_(0), health_(500), keys_(0), health_timer_(0) {
  init_stats();
}

void Player::handle_inputs(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_w:     actor_.move_up_    = true; break;
      case SDLK_a:     actor_.move_left_  = true; break;
      case SDLK_s:     actor_.move_down_  = true; break;
      case SDLK_d:     actor_.move_right_ = true; break;
      case SDLK_SPACE: actor_.firing_     = true; break;
      default: break;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_w:     actor_.move_up_    = false; break;
      case SDLK_a:     actor_.move_left_  = false; break;
      case SDLK_s:     actor_.move_down_  = false; break;
      case SDLK_d:     actor_.move_right_ = false; break;
      case SDLK_SPACE: actor_.firing_     = false; break;
      default: break;
    }
  }
}

void Player::move(int pixels){
  // Diagonal movement
  if (actor_.move_up_ && actor_.move_right_) {
    actor_.position_.y -= pixels;
    actor_.position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingUpRight);
    actor_.last_state_ = AnimationState::kIdleUpRight;
    actor_.direction_ = Direction::kUpRight;
  } else if (actor_.move_up_ && actor_.move_left_) {
    actor_.position_.y -= pixels;
    actor_.position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingUpLeft);
    actor_.last_state_ = AnimationState::kIdleUpLeft;
    actor_.direction_ = Direction::kUpLeft;
  } else if (actor_.move_down_ && actor_.move_right_) {
    actor_.position_.y += pixels;
    actor_.position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingDownRight);
    actor_.last_state_ = AnimationState::kIdleDownRight;
    actor_.direction_ = Direction::kDownRight;
  } else if (actor_.move_down_ && actor_.move_left_) {
    actor_.position_.y += pixels;
    actor_.position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingDownLeft);
    actor_.last_state_ = AnimationState::kIdleDownLeft;
    actor_.direction_ = Direction::kDownLeft;
  }
  // Single axis movement
  else if (actor_.move_up_) {
    actor_.position_.y -= pixels;
    sprite_.set_animation(AnimationState::kMovingUp);
    actor_.last_state_ = AnimationState::kIdleUp;
    actor_.direction_ = Direction::kUp;
  } else if (actor_.move_down_) {
    actor_.position_.y += pixels;
    sprite_.set_animation(AnimationState::kMovingDown);
    actor_.last_state_ = AnimationState::kIdleDown;
    actor_.direction_ = Direction::kDown;
  } else if (actor_.move_left_) {
    actor_.position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingLeft);
    actor_.last_state_ = AnimationState::kIdleLeft;
    actor_.direction_ = Direction::kLeft;
  } else if (actor_.move_right_) {
    actor_.position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingRight);
    actor_.last_state_ = AnimationState::kIdleRight;
    actor_.direction_ = Direction::kRight;
  }
}

// Function to be called to update the game state of the player
void Player::update(World& world) {

  if(actor_.dying_){
    sprite_.update();
    if(sprite_.ended_){
      actor_.dead_ = true;
    }
    return;
  }

  actor_.last_position_ = actor_.position_;
  
  if(actor_.firing_) {
    fire(world);
  } else {
    move(actor_.movespeed_);

    if (!actor_.move_right_ && !actor_.move_down_ && !actor_.move_up_ && !actor_.move_left_) {
      // Set idle animation to last direction moved in
      sprite_.set_animation(actor_.last_state_);
    }
  }
  
  tick_health();
  sprite_.update();
}

void Player::damage(){
  health_ -= damage_per_hit;
  notify(GameEvent::kPlayerDamage);

  if(health_ < 1 ){
    notify(GameEvent::kPlayerDeath);
  }
}

// Fires projectile to world
void Player::fire(World& world){
  Uint32 current = SDL_GetTicks() - actor_.last_fire_;
  move(0);
  sprite_.set_firing_animation(actor_.direction_);
  if(current > actor_.fire_rate_) {
    notify(GameEvent::kPlayerFire);
    world.player_projectiles_.push_back(
      Projectile{actor_.position_, actor_.direction_, sprite_.sprite_class_, 0});
    actor_.last_fire_ = SDL_GetTicks();
  }
}

// Player loses 1hp every second
void Player::tick_health(){
  Uint32 current = SDL_GetTicks();
  if(current - health_timer_ > 1000){
    health_ --;
    health_timer_ = current;
    notify(GameEvent::kPlayerTickDamage);
  }

  if(health_ < 1 ){
    notify(GameEvent::kPlayerDeath);
  }
}

// All pickup types still need to be implemented
void Player::pickup_item(Pickup pickup){
  switch (pickup.pickup_type_) {

    case PickupType::kPoints: 
      score_ += 100;
      notify(GameEvent::kPointPickup);
      break;
    case PickupType::kHealth:
      health_ += 100;
      notify(GameEvent::kHealthPickup);
      break;
    case PickupType::kHealthPotion:
      // TODO: implement potions
      notify(GameEvent::kHealthPotionPickup);
      break;
    case PickupType::kDestroyPotion:
      // TODO: implement potions
      notify(GameEvent::kDestroyPotionPickup);
      break;
    case PickupType::kKey:
      keys_++;
      notify(GameEvent::kKeyPickup);
      break;
    case PickupType::kExit:
      notify(GameEvent::kLevelExit);
      break;
    }
}

void Player::init_stats(){
  switch (player_class_) {
    case PlayerClass::kWarrior: 
      sprite_ = {SpriteClass::kWarrior};
      damage_per_hit = 3;
      actor_.movespeed_ = 3;
      break;
    case PlayerClass::kValkyrie: 
      sprite_ = {SpriteClass::kValkyrie};
      damage_per_hit = 5;
      actor_.movespeed_ = 3; 
      break;
    case PlayerClass::kWizard: 
      sprite_ = {SpriteClass::kWizard}; 
      damage_per_hit = 8;
      actor_.movespeed_ = 4;      
      break;
    case PlayerClass::kElf: 
      sprite_ = {SpriteClass::kElf};
      damage_per_hit = 10;
      actor_.movespeed_ = 5;
      actor_.fire_rate_ = 150;
      break;
  }
}