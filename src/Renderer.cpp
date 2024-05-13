#include "Renderer.hpp"
#include "World.hpp"
#include <sstream>

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen)
  :sprite_sheet_(sprite_sheet), screen_(screen){
  TTF_Init();
  font_ = TTF_OpenFont("<!Gauntlet$Dir>.Font", 28);
};

Renderer::Renderer()
  : level_background_(nullptr),
    sprite_sheet_(nullptr),
    screen_(nullptr),
    font_(nullptr) {
}

Renderer::~Renderer() {
  SDL_FreeSurface(sprite_sheet_);
  sprite_sheet_ = nullptr;
  
  SDL_FreeSurface(screen_);
  screen_ = nullptr;
    
  if (level_background_ != nullptr) {
    SDL_FreeSurface(level_background_);
    level_background_ = nullptr;
  }
    
  TTF_CloseFont(font_);
  font_ = nullptr;
}

void Renderer::destory(){
  this->~Renderer();
}

void Renderer::clear(){
  SDL_FillRect(screen_, nullptr, screen_clear_color_);
}

void Renderer::render(const Actor& actor){
  SDL_Rect sprite = actor.sprite_.get_frame();
  if(is_zero(sprite)){
    return;
  }
  SDL_Rect position = actor.position_;
  // std::stringstream message;
  // message << "position:" << actor.position_.x << " , " << actor.position_.y;
  // render_text(message, {400,400});
  // SDL_Rect position = {96,96};
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

void Renderer::render(const Projectile& projectile){
  SDL_Rect sprite = projectile.sprite_.get_frame();

  if(is_zero(sprite)){
    return;
  }

  SDL_Rect position = projectile.position_;
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

void Renderer::render_map(const Player& player) {
  SDL_Rect sprite = {0,0,960,640};
  SDL_Rect position = {0,0};
  SDL_BlitSurface(level_background_, &sprite, screen_, &position);
}

void Renderer::render_text(std::stringstream& message_string, SDL_Rect location) {
  SDL_Surface* message = TTF_RenderText_Solid(font_, message_string.str().c_str(), text_color_);

  SDL_BlitSurface(message, nullptr, screen_, &location);
  // SDL_FreeSurface( message );
}

void Renderer::render_frame(){
  SDL_Flip(screen_);
}

bool Renderer::is_zero(SDL_Rect& sprite) {
  return sprite.h == 0 && sprite.w == 0;
}