#include "Sprite.hpp"

Sprite::Sprite(SpriteClass sprite_class)
  : sprite_class_(sprite_class){

}

void Sprite::add_animation(AnimationState state, std::vector<SpriteIndex> frames){
  animations_[state] = frames;
}

void Sprite::set_animation(AnimationState state){
  if (current_state_ != state) {
    current_state_ = state;
    current_frames_ = &animations_[state];
    current_frame_ = 0; // Reset to the first frame
  }
}

void Sprite::update(){
  Uint32 frame_time = SDL_GetTicks() - last_frame_time_;
  if (current_frames_ && !current_frames_->empty() && frame_time > 50) {
    current_frame_ = (current_frame_ + 1) % current_frames_->size();
    last_frame_time_ = SDL_GetTicks();
  }
}

SDL_Rect Sprite::get_frame() const {
  if (current_frames_ && !current_frames_->empty()) {
    SpriteIndex& point = (*current_frames_)[current_frame_];
    return {point, static_cast<Sint16>(sprite_class_), 32, 32};
  }
  // Handle case where current_frames_ is null or empty
  return {0, 0, 0, 0};
}
 