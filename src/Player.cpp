#include "Player.hpp"

Player::Player(SDL_Surface* spriteSheet, SDL_Surface* screen) 
  : Character(spriteSheet, screen){
    init_animations(sprite_);
}

void Player::handle_inputs(const SDL_Event& event){
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_w: move_up_ = true; break;
      case SDLK_a: move_left_ = true; break;
      case SDLK_s: move_down_ = true; break;
      case SDLK_d: move_right_ = true; break;
      default: break;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_w: move_up_ = false; break;
      case SDLK_a: move_left_ = false; break;
      case SDLK_s: move_down_ = false; break;
      case SDLK_d: move_right_ = false; break;
      default: break;
    }
  }
}

void Player::select_player_class(PlayerClass player_class){
  player_class_ = player_class;
  switch (player_class_) {
    case PlayerClass::kWarrior: 
      sprite_.set_sprite_class(SpriteClass::kWarrior); break;
    case PlayerClass::kValkyrie: 
      sprite_.set_sprite_class(SpriteClass::kValkyrie); break;
    case PlayerClass::kWizard: 
      sprite_.set_sprite_class(SpriteClass::kWizard); break;
    case PlayerClass::kArcher: 
      sprite_.set_sprite_class(SpriteClass::kArcher); break;
  }
}

void Player::update(){
  // Diagonal movement
  if (move_up_ && move_right_) {
    position_.y -= 4;
    position_.x += 4;
    sprite_.set_animation(AnimationState::kRunningUpRight);
    direction_ = AnimationState::kIdleUpRight;
  } else if (move_up_ && move_left_) {
    position_.y -= 4;
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kRunningUpLeft);
    direction_ = AnimationState::kIdleUpLeft;
  } else if (move_down_ && move_right_) {
    position_.y += 4;
    position_.x += 4;
    sprite_.set_animation(AnimationState::kRunningDownRight);
    direction_ = AnimationState::kIdleDownRight;
  } else if (move_down_ && move_left_) {
    position_.y += 4;
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kRunningDownLeft);
    direction_ = AnimationState::kIdleDownLeft;
  }
  // Single axis movement
  else if (move_up_) {
    position_.y -= 4;
    sprite_.set_animation(AnimationState::kRunningUp);
    direction_ = AnimationState::kIdleUp;
  } else if (move_down_) {
    position_.y += 4;
    sprite_.set_animation(AnimationState::kRunningDown);
    direction_ = AnimationState::kIdleDown;
  } else if (move_left_) {
    position_.x -= 4;
    sprite_.set_animation(AnimationState::kRunningLeft);
    direction_ = AnimationState::kIdleLeft;
  } else if (move_right_) {
    position_.x += 4;
    sprite_.set_animation(AnimationState::kRunningRight);
    direction_ = AnimationState::kIdleRight;
  }

  if (!move_right_ && !move_down_ && !move_up_ && !move_left_) {
    // Set idle animation to last direction moved in
    sprite_.set_animation(direction_);
  }

  sprite_.update();
}

void Player::init_animations(Sprite& sprite){
  sprite.add_animation(AnimationState::kRunningUp, 
    std::vector<SpriteIndex>{0, 256, 512});

  sprite.add_animation(AnimationState::kRunningUpRight, 
    std::vector<SpriteIndex>{32,288,544});

  sprite.add_animation(AnimationState::kRunningRight,
    std::vector<SpriteIndex>{64,320,576});

  sprite.add_animation(AnimationState::kRunningDownRight,
    std::vector<SpriteIndex>{96,352,608});
  
  sprite.add_animation(AnimationState::kRunningDown, 
    std::vector<SpriteIndex>{128,384, 640});

  sprite.add_animation(AnimationState::kRunningDownLeft,
    std::vector<SpriteIndex>{160,416,672});

  sprite.add_animation(AnimationState::kRunningLeft,
    std::vector<SpriteIndex>{192,448,704});
  
  sprite.add_animation(AnimationState::kRunningUpLeft,
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