#include "Renderer.hpp"
#include "SDL/SDL_video.h"

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen)
  :sprite_sheet_(sprite_sheet), screen_(screen), title_screen_(title_screen){
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

  if (title_screen_ != nullptr) {
    SDL_FreeSurface(title_screen_);
    title_screen_ = nullptr;
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

void Renderer::render(const Actor& actor) const {
  SDL_Rect position = actor.position_;

  if(clip(position)){
    return;
  }

  SDL_Rect sprite = actor.sprite_.get_frame();

  if(is_zero(sprite)){
    return;
  }

  // Camera offset
  position.x -= camera_.x;
  position.y -= camera_.y;

  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

void Renderer::render(const Projectile& projectile) const {

  SDL_Rect position = projectile.position_;

  if(clip(position)){
    return;
  }

  SDL_Rect sprite = projectile.sprite_.get_frame();

  if(is_zero(sprite)){
    return;
  }

  // Camera offset
  position.x -= camera_.x;
  position.y -= camera_.y;
  SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position);
}

void Renderer::render_map(const Player& player) {
 // Calculate the center of the camera
  Sint16 camera_centre_x = camera_.x + camera_.w / 2;
  Sint16 camera_centre_y = camera_.y + camera_.h / 2;

  // Calculate the offset of the player from the camera center
  Sint16 dx = player.position_.x - camera_centre_x;
  Sint16 dy = player.position_.y - camera_centre_y;

  // Update camera position to center on the player
  camera_.x += dx;
  camera_.y += dy;

  // Clamp camera to stay within the bounds of the map
  if (camera_.x < 0) {
    camera_.x = 0;
  }
  if (camera_.y < 0) {
    camera_.y = 0;
  }

  if (camera_.x + camera_.w > level_background_->w) {
    camera_.x = level_background_->w - camera_.w;
  }
  if (camera_.y + camera_.h > level_background_->h) {
    camera_.y = level_background_->h - camera_.h;
  }

  SDL_BlitSurface(level_background_, &camera_, screen_, NULL);
}

void Renderer::render_title() const{

  SDL_Rect position {0,0,960,640};
  SDL_Rect dest {0,0,960,640};
  SDL_BlitSurface(title_screen_, &position, screen_, &dest);
}

void Renderer::render_sidebar() {
  SDL_Rect ui {960,0, 240, 640};
  SDL_FillRect(screen_, &ui, SDL_MapRGB(screen_->format, 0, 0, 255));
}

void Renderer::render_text(const std::string& message_string, SDL_Rect location) {
  SDL_Surface* message = TTF_RenderText_Solid(font_, message_string.c_str(), text_color_);

  SDL_BlitSurface(message, nullptr, screen_, &location);
  SDL_FreeSurface( message );
}

void Renderer::render_frame() const {
  SDL_Flip(screen_);
}

bool Renderer::is_zero(SDL_Rect& sprite) const {
  return sprite.h == 0 && sprite.w == 0;
}

bool Renderer::clip(SDL_Rect& location) const {
  return location.y > camera_.y + camera_.h ||
         location.x > camera_.x + camera_.w ||
         location.y + 32 < camera_.y ||
         location.x + 32 < camera_.x;
}