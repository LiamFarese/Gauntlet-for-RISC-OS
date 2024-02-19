#include "Player.hpp"
#include "Sprite.hpp"

Player::Player(SDL_Surface* spriteSheet, SDL_Surface* screen) 
  : Character(spriteSheet, screen){
    initAnimations(m_sprite);
}

void Player::handleInputs(const SDL_Event& event){
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_w: m_moveUp = true; break;
      case SDLK_a: m_moveLeft = true; break;
      case SDLK_s: m_moveDown = true; break;
      case SDLK_d: m_moveRight = true; break;
      default: break;
    }
  } else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
      case SDLK_w: m_moveUp = false; break;
      case SDLK_a: m_moveLeft = false; break;
      case SDLK_s: m_moveDown = false; break;
      case SDLK_d: m_moveRight = false; break;
      default: break;
    }
  }
}

// TODO: implement other player classes
void Player::selectPlayerClass(PlayerClass playerClass){
  m_playerClass = playerClass;
  switch (m_playerClass) {
    case PlayerClass::Warrior: m_sprite.setSpriteClass(SpriteClass::Warrior); break;
    case PlayerClass::Valkyrie: m_sprite.setSpriteClass(SpriteClass::Valkyrie); break;
    case PlayerClass::Wizard: m_sprite.setSpriteClass(SpriteClass::Wizard); break;
    case PlayerClass::Archer: m_sprite.setSpriteClass(SpriteClass::Archer); break;

  }
}

void Player::update(){
  // Diagonal movement
  if (m_moveUp && m_moveRight) {
    m_position.y -= 4;
    m_position.x += 4;
    m_sprite.setAnimation(AnimationState::RunningUpRight);
    m_direction = AnimationState::IdleUpRight;
  } else if (m_moveUp && m_moveLeft) {
    m_position.y -= 4;
    m_position.x -= 4;
    m_sprite.setAnimation(AnimationState::RunningUpLeft);
    m_direction = AnimationState::IdleUpLeft;
  } else if (m_moveDown && m_moveRight) {
    m_position.y += 4;
    m_position.x += 4;
    m_sprite.setAnimation(AnimationState::RunningDownRight);
    m_direction = AnimationState::IdleDownRight;
  } else if (m_moveDown && m_moveLeft) {
    m_position.y += 4;
    m_position.x -= 4;
    m_sprite.setAnimation(AnimationState::RunningDownLeft);
    m_direction = AnimationState::IdleDownLeft;
  }
  // Single axis movement
  else if (m_moveUp) {
    m_position.y -= 4;
    m_sprite.setAnimation(AnimationState::RunningUp);
    m_direction = AnimationState::IdleUp;
  } else if (m_moveDown) {
    m_position.y += 4;
    m_sprite.setAnimation(AnimationState::RunningDown);
    m_direction = AnimationState::IdleDown;
  } else if (m_moveLeft) {
    m_position.x -= 4;
    m_sprite.setAnimation(AnimationState::RunningLeft);
    m_direction = AnimationState::IdleLeft;
  } else if (m_moveRight) {
    m_position.x += 4;
    m_sprite.setAnimation(AnimationState::RunningRight);
    m_direction = AnimationState::IdleRight;
  }

  if (!m_moveRight && !m_moveDown && !m_moveUp && !m_moveLeft) {
    // Set idle animation to last direction moved in
    m_sprite.setAnimation(m_direction);
  }

  m_sprite.update();
}

void Player::initAnimations(Sprite& sprite){
  sprite.addAnimation(AnimationState::RunningUp, 
    std::vector<SpriteIndex>{0, 256, 512});

  sprite.addAnimation(AnimationState::RunningUpRight, 
    std::vector<SpriteIndex>{32,288,544});

  sprite.addAnimation(AnimationState::RunningRight,
    std::vector<SpriteIndex>{64,320,576});

  sprite.addAnimation(AnimationState::RunningDownRight,
    std::vector<SpriteIndex>{96,352,608});
  
  sprite.addAnimation(AnimationState::RunningDown, 
    std::vector<SpriteIndex>{128,384, 640});

  sprite.addAnimation(AnimationState::RunningDownLeft,
    std::vector<SpriteIndex>{160,416,672});

  sprite.addAnimation(AnimationState::RunningLeft,
    std::vector<SpriteIndex>{192,448,704});
  
  sprite.addAnimation(AnimationState::RunningUpLeft,
    std::vector<SpriteIndex>{224,480,736});
    
  sprite.addAnimation(AnimationState::IdleUp, 
    std::vector<SpriteIndex>{0});
  
  sprite.addAnimation(AnimationState::IdleUpRight,
    std::vector<SpriteIndex>{32});

  sprite.addAnimation(AnimationState::IdleRight,
    std::vector<SpriteIndex>{64});

  sprite.addAnimation(AnimationState::IdleDownRight,
    std::vector<SpriteIndex>{96});

  sprite.addAnimation(AnimationState::IdleDown,
    std::vector<SpriteIndex>{128});

  sprite.addAnimation(AnimationState::IdleDownLeft,
    std::vector<SpriteIndex>{160});
  
  sprite.addAnimation(AnimationState::IdleLeft,
    std::vector<SpriteIndex>{192});
  
  sprite.addAnimation(AnimationState::IdleUpLeft,
    std::vector<SpriteIndex>{224});

  sprite.setAnimation(AnimationState::IdleDown);
  
}