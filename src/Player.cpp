#include "Player.hpp"

#include "Models.hpp"
#include "SoundManager.hpp"
#include "UIManager.hpp"
#include "World.hpp"

Player::Player(PlayerClass player_class, UIManager& ui_manager, SoundManager& sound_manager) 
  : player_class_(player_class), ui_manager_(ui_manager), score_(0), health_(500), health_timer_(0),sound_manager_(sound_manager) {
  switch (player_class_) {
    case PlayerClass::kWarrior: 
      sprite_ = {SpriteClass::kWarrior};
      damage_per_hit = 3;
      movespeed_ = 7;
      break;
    case PlayerClass::kValkyrie: 
      sprite_ = {SpriteClass::kValkyrie};
      damage_per_hit = 5;
      movespeed_ = 7; 
      break;
    case PlayerClass::kWizard: 
      sprite_ = {SpriteClass::kWizard}; 
      damage_per_hit = 8;
      movespeed_ = 9;      
      break;
    case PlayerClass::kElf: 
      sprite_ = {SpriteClass::kElf};
      damage_per_hit = 10;
      movespeed_ = 10;
      fire_rate_ = 300;
      break;
  }
}

void Player::handle_inputs(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_w:     move_up_    = true; break;
      case SDLK_a:     move_left_  = true; break;
      case SDLK_s:     move_down_  = true; break;
      case SDLK_d:     move_right_ = true; break;
      case SDLK_SPACE: firing_     = true; break;
      default: break;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_w:     move_up_    = false; break;
      case SDLK_a:     move_left_  = false; break;
      case SDLK_s:     move_down_  = false; break;
      case SDLK_d:     move_right_ = false; break;
      case SDLK_SPACE: firing_     = false; break;
      default: break;
    }
  }
}

void Player::move(int pixels){
  // Diagonal movement
  if (move_up_ && move_right_) {
    position_.y -= pixels;
    position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingUpRight);
    last_state_ = AnimationState::kIdleUpRight;
    direction_ = Direction::kUpRight;
  } else if (move_up_ && move_left_) {
    position_.y -= pixels;
    position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingUpLeft);
    last_state_ = AnimationState::kIdleUpLeft;
    direction_ = Direction::kUpLeft;
  } else if (move_down_ && move_right_) {
    position_.y += pixels;
    position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingDownRight);
    last_state_ = AnimationState::kIdleDownRight;
    direction_ = Direction::kDownRight;
  } else if (move_down_ && move_left_) {
    position_.y += pixels;
    position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingDownLeft);
    last_state_ = AnimationState::kIdleDownLeft;
    direction_ = Direction::kDownLeft;
  }
  // Single axis movement
  else if (move_up_) {
    position_.y -= pixels;
    sprite_.set_animation(AnimationState::kMovingUp);
    last_state_ = AnimationState::kIdleUp;
    direction_ = Direction::kUp;
  } else if (move_down_) {
    position_.y += pixels;
    sprite_.set_animation(AnimationState::kMovingDown);
    last_state_ = AnimationState::kIdleDown;
    direction_ = Direction::kDown;
  } else if (move_left_) {
    position_.x -= pixels;
    sprite_.set_animation(AnimationState::kMovingLeft);
    last_state_ = AnimationState::kIdleLeft;
    direction_ = Direction::kLeft;
  } else if (move_right_) {
    position_.x += pixels;
    sprite_.set_animation(AnimationState::kMovingRight);
    last_state_ = AnimationState::kIdleRight;
    direction_ = Direction::kRight;
  }
}

// Function to be called to update the game state of the player
void Player::update(World& world) {

  if(dying_){
    sprite_.update();
    if(sprite_.ended_){
      dead_ = true;
    }
    return;
  }

  last_position_ = position_;
  
  if(firing_) {
    fire(world);
  } else {
    move(movespeed_);

    if (!move_right_ && !move_down_ && !move_up_ && !move_left_) {
      // Set idle animation to last direction moved in
      sprite_.set_animation(last_state_);
    }
  }
  
  tick_health();
  sprite_.update();
}

void Player::fire(World& world){
  Uint32 current = SDL_GetTicks() - last_fire_;
  move(0);
  set_firing_animation();
  if(current > fire_rate_) {
    notify(GameEvent::kPlayerFire);
    world.player_projectiles_.push_back(
      Projectile{position_, direction_, sprite_.sprite_class_, 0});
    last_fire_ = SDL_GetTicks();
  }
}

void Player::damage(){
  health_ -= damage_per_hit;
  notify(GameEvent::kPlayerDamage);
}

// Player loses 1hp every second
void Player::tick_health(){
  Uint32 current = SDL_GetTicks();
  if(current - health_timer_ > 1000){
    health_ --;
    health_timer_ = current;
    notify(GameEvent::kPlayerTickDamage);
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
    case PickupType::kHealthPotion:
      // TODO: implement potions
      notify(GameEvent::kHealthPotionPickup);
    case PickupType::kDestroyPotion:
      // TODO: implement potions
      notify(GameEvent::kDestroyPotionPickup);
    case PickupType::kKey:
      // TODO: implement keys  
      notify(GameEvent::kKeyPickup);
      break;
    case PickupType::kExit:
      // TODO: implement next levels
      notify(GameEvent::kLevelExit);
      break;
    }
}

void Player::notify(GameEvent event){
  sound_manager_.on_notify(event);
  ui_manager_.on_notify(event);
}