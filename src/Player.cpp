#include "Player.hpp"
#include "SDL/SDL_timer.h"

#include <memory>

Player::Player() 
  : Actor() {
    init_animations(sprite_);
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
    case PlayerClass::kArcher: 
      sprite_.sprite_class_ = SpriteClass::kArcher; break;
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

void Player::update(World& world) {
  // Diagonal movement
  if (move_up_ && move_right_) {
    position_.y -= 4;
    position_.x += 4;
    sprite_.set_animation(AnimationState::kMovingUpRight);
    last_state_ = AnimationState::kIdleUpRight;
    direction_ = Direction::kUpRight;
  } else if (move_up_ && move_left_) {
    position_.y -= 4;
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kMovingUpLeft);
    last_state_ = AnimationState::kIdleUpLeft;
    direction_ = Direction::kUpLeft;
  } else if (move_down_ && move_right_) {
    position_.y += 4;
    position_.x += 4;
    sprite_.set_animation(AnimationState::kMovingDownRight);
    last_state_ = AnimationState::kIdleDownRight;
    direction_ = Direction::kDownRight;
  } else if (move_down_ && move_left_) {
    position_.y += 4;
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kMovingDownLeft);
    last_state_ = AnimationState::kIdleDownLeft;
    direction_ = Direction::kDownLeft;
  }
  // Single axis movement
  else if (move_up_) {
    position_.y -= 4;
    sprite_.set_animation(AnimationState::kMovingUp);
    last_state_ = AnimationState::kIdleUp;
    direction_ = Direction::kUp;
  } else if (move_down_) {
    position_.y += 4;
    sprite_.set_animation(AnimationState::kMovingDown);
    last_state_ = AnimationState::kIdleDown;
    direction_ = Direction::kDown;
  } else if (move_left_) {
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kMovingLeft);
    last_state_ = AnimationState::kIdleLeft;
    direction_ = Direction::kLeft;
  } else if (move_right_) {
    position_.x += 4;
    sprite_.set_animation(AnimationState::kMovingRight);
    last_state_ = AnimationState::kIdleRight;
    direction_ = Direction::kRight;
  }

  Uint32 current = SDL_GetTicks() - last_fire_; 
  if(firing_ && current > 200) {
    world.player_projectiles_.push_back(std::move(Projectile{position_, direction_, sprite_.sprite_class_}));
    last_fire_ = SDL_GetTicks();
  }

  if (!move_right_ && !move_down_ && !move_up_ && !move_left_) {
    // Set idle animation to last direction moved in
    sprite_.set_animation(last_state_);
  }

  sprite_.update();
}

void Player::init_animations(Sprite& sprite) {
  sprite.add_animation(AnimationState::kMovingUp, 
    std::vector<SpriteIndex>{0, 256, 512});

  sprite.add_animation(AnimationState::kMovingUpRight, 
    std::vector<SpriteIndex>{32,288,544});

  sprite.add_animation(AnimationState::kMovingRight,
    std::vector<SpriteIndex>{64,320,576});

  sprite.add_animation(AnimationState::kMovingDownRight,
    std::vector<SpriteIndex>{96,352,608});
  
  sprite.add_animation(AnimationState::kMovingDown, 
    std::vector<SpriteIndex>{128,384, 640});

  sprite.add_animation(AnimationState::kMovingDownLeft,
    std::vector<SpriteIndex>{160,416,672});

  sprite.add_animation(AnimationState::kMovingLeft,
    std::vector<SpriteIndex>{192,448,704});
  
  sprite.add_animation(AnimationState::kMovingUpLeft,
    std::vector<SpriteIndex>{224,480,736});
    
  sprite.add_animation(AnimationState::kIdleUp, 
    std::vector<SpriteIndex>{0});
  
  sprite.add_animation(AnimationState::kIdleUpRight,
    std::vector<SpriteIndex>{32});

  sprite.add_animation(AnimationState::kIdleRight,
    std::vector<SpriteIndex>{64});

  sprite.add_animation(AnimationState::kIdleDownRight,
    std::vector<SpriteIndex>{96});

  sprite.add_animation(AnimationState::kIdleDown,
    std::vector<SpriteIndex>{128});

  sprite.add_animation(AnimationState::kIdleDownLeft,
    std::vector<SpriteIndex>{160});
  
  sprite.add_animation(AnimationState::kIdleLeft,
    std::vector<SpriteIndex>{192});
  
  sprite.add_animation(AnimationState::kIdleUpLeft,
    std::vector<SpriteIndex>{224});

  sprite.set_animation(AnimationState::kIdleDown);
  
}