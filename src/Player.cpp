#include "Player.hpp"
#include "Projectile.hpp"
#include "Sprite.hpp"
#include <SDL/SDL.h>

#include <memory>

Player::Player() 
  : Actor() {
}

void Player::select_player_class(PlayerClass player_class) noexcept {
  player_class_ = player_class;
  switch (player_class_) {
    case PlayerClass::kWarrior: 
      sprite_.sprite_class_ = SpriteClass::kWarrior; break;
    case PlayerClass::kValkyrie: 
      sprite_.sprite_class_ = SpriteClass::kValkyrie; break;
    case PlayerClass::kWizard: 
      sprite_.sprite_class_ = SpriteClass::kWizard; break;
    case PlayerClass::kElf: 
      sprite_.sprite_class_ = SpriteClass::kElf; break;
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

void Player::set_firing_animation(Direction direction){
  switch (direction) {
    case Direction::kUp:
      sprite_.set_animation(AnimationState::kMovingUp); break;
    case Direction::kDown:
      sprite_.set_animation(AnimationState::kMovingDown); break;
    case Direction::kLeft:
      sprite_.set_animation(AnimationState::kMovingLeft); break;
    case Direction::kRight:
      sprite_.set_animation(AnimationState::kMovingRight); break;
    case Direction::kUpRight:
      sprite_.set_animation(AnimationState::kMovingUpRight); break;
    case Direction::kUpLeft:
      sprite_.set_animation(AnimationState::kMovingUpLeft); break;
    case Direction::kDownRight:
      sprite_.set_animation(AnimationState::kMovingDownRight); break;
    case Direction::kDownLeft:
      sprite_.set_animation(AnimationState::kMovingDownLeft); break;
     default:
      break;
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

void Player::update(World& world) {
  last_position_ = position_;
  
  Uint32 current = SDL_GetTicks() - last_fire_;
  if(firing_) {
    move(0);
    set_firing_animation(direction_);
    if(current > 200) {
      world.player_projectiles_.push_back(std::move(Projectile{position_, direction_, sprite_.sprite_class_}));
      last_fire_ = SDL_GetTicks();
    }
  } else {
    move(6);

    if (!move_right_ && !move_down_ && !move_up_ && !move_left_) {
      // Set idle animation to last direction moved in
      sprite_.set_animation(last_state_);
    }
  }

  sprite_.update();
}
