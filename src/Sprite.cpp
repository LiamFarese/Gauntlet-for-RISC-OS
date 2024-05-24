#include "Sprite.hpp"
#include "Models.hpp"

Sprite::Sprite(SpriteClass sprite_class)
  : sprite_class_(sprite_class) {
}

const Sprite::AnimationFrames Sprite::animations_ = {
  std::vector<Sint16>{0, 256, 512},          // kMovingUp
  std::vector<Sint16>{32, 288, 544},         // kMovingUpRight
  std::vector<Sint16>{64, 320, 576},         // kMovingRight
  std::vector<Sint16>{96, 352, 608},         // kMovingDownRight
  std::vector<Sint16>{128, 384, 640},        // kMovingDown
  std::vector<Sint16>{160, 416, 672},        // kMovingDownLeft
  std::vector<Sint16>{192, 448, 704},        // kMovingLeft
  std::vector<Sint16>{224, 480, 736},        // kMovingUpLeft
  std::vector<Sint16>{0},                    // kIdleUp
  std::vector<Sint16>{32},                   // kIdleUpRight
  std::vector<Sint16>{64},                   // kIdleRight
  std::vector<Sint16>{96},                   // kIdleDownRight
  std::vector<Sint16>{128},                  // kIdleDown
  std::vector<Sint16>{160},                  // kIdleDownLeft
  std::vector<Sint16>{192},                  // kIdleLeft
  std::vector<Sint16>{224},                  // kIdleUpLeft
  std::vector<Sint16>{768, 800, 832, 864, 896, 928, 960, 992}, // kAxe
  std::vector<Sint16>{768},                  // kProjectileUp
  std::vector<Sint16>{800},                  // kProjectileUpRight
  std::vector<Sint16>{832},                  // kProjectileRight
  std::vector<Sint16>{864},                  // kProjectileDownRight
  std::vector<Sint16>{896},                  // kProjectileDown
  std::vector<Sint16>{928},                  // kProjectileDownLeft
  std::vector<Sint16>{960},                  // kProjectileLeft
  std::vector<Sint16>{992},                  // kProjectileUpLeft
  std::vector<Sint16>{608, 640},             // kProjectileDestroyed
  std::vector<Sint16>{416, 448, 480, 512, 544, 576} // kDeath
};

void Sprite::set_animation(AnimationState state) {
  if (current_state_ != state) {
    current_state_ = state;
    current_frames_ = &animations_[static_cast<Sint16>(state)];
    // Keep enemy animations out of sync
    if(static_cast<Sint16>(sprite_class_) > 100 && current_frames_){
      current_frame_ = rand() % current_frames_->size();
    }else{
      current_frame_ = 0; // Reset to the first frame
    }
  }
}

void Sprite::set_firing_animation(Direction direction){
  switch (direction) {
    case Direction::kUp:
      set_animation(AnimationState::kMovingUp); break;
    case Direction::kDown:
      set_animation(AnimationState::kMovingDown); break;
    case Direction::kLeft:
      set_animation(AnimationState::kMovingLeft); break;
    case Direction::kRight:
      set_animation(AnimationState::kMovingRight); break;
    case Direction::kUpRight:
      set_animation(AnimationState::kMovingUpRight); break;
    case Direction::kUpLeft:
      set_animation(AnimationState::kMovingUpLeft); break;
    case Direction::kDownRight:
      set_animation(AnimationState::kMovingDownRight); break;
    case Direction::kDownLeft:
      set_animation(AnimationState::kMovingDownLeft); break;
     default:
      break;
  }
}

void Sprite::update() {
  Uint32 frame_time = SDL_GetTicks() - last_frame_time_;
  if (current_frames_ && !current_frames_->empty() && frame_time > 50) {
    if(current_state_ == AnimationState::kDeath || current_state_ == AnimationState::kProjectileDestroyed){
      current_frame_ += 1;
      if(!(current_frame_ < current_frames_->size())){
        ended_ = true;
      }
    } else {
      current_frame_ = (current_frame_ + 1) % current_frames_->size();
    }
    last_frame_time_ = SDL_GetTicks();
  }
}

SDL_Rect Sprite::get_frame() const {
  SDL_Rect sprite{0,0,0,0};
  if(current_state_ == AnimationState::kDeath || current_state_ == AnimationState::kProjectileDestroyed){
    if(current_frames_ && !ended_){
      const Sint16& point = (*current_frames_)[current_frame_];
      sprite = {point, 288, 32, 32};
    }
  } else if (current_frames_ && !ended_) {
    const Sint16& point = (*current_frames_)[current_frame_];
    sprite = {point, static_cast<Sint16>(sprite_class_), 32, 32};
  }
  return sprite;
}

 