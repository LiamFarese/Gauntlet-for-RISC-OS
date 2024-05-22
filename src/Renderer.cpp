#include "Renderer.hpp"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_video.h"

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen, SDL_Surface* logo)
  :sprite_sheet_(sprite_sheet), screen_(screen), title_screen_(title_screen), logo_(logo), ui_rendered_(0) {
  TTF_Init();
  font_ = TTF_OpenFont("<!Gauntlet$Dir>.Font", 20);
  title_font_ = TTF_OpenFont("<!Gauntlet$Dir>.Font", 30);

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

void Renderer::render_sidebar(UIManager& ui_manager) {
  // clear background and set it to black
  SDL_Rect ui {960,100, 240, 640};
  SDL_FillRect(screen_, &ui, SDL_MapRGB(screen_->format, 0, 0, 0));

  render_static_ui();

  Sint16 score_and_health_y = 0;
  switch(ui_manager.player_class_){
    case PlayerClass::kWarrior: score_and_health_y = 222; break; 
    case PlayerClass::kValkyrie: score_and_health_y = 344; break; 
    case PlayerClass::kWizard: score_and_health_y = 466; break; 
    case PlayerClass::kElf: score_and_health_y = 588; break; 
    default: break;
  }

  std::string default_values = "000";
  if(ui_manager.game_running){
    
    render_text(ui_manager.health_str, {1110, score_and_health_y});
    render_text(ui_manager.score_str, {1030, score_and_health_y});

    Sint16 y_location = 222;
    for(int i = 0; i < 4; i++){
      render_text("health:", {1110, static_cast<Sint16>(y_location-30)});
      render_text("score:", {1030, static_cast<Sint16>(y_location-30)});
      if(i != static_cast<Sint16>(ui_manager.player_class_)){
        render_text(default_values, {1110, y_location});
        render_text(default_values, {1030, y_location});
      }
      y_location += 122;
    }
  } else {
    Sint16 y_location = 222;
    std::string prompt = "press          to play";
    std::stringstream number;
    SDL_Rect location{1075};
    for(int i = 0; i < 4; i++){
      SDL_Color class_color;
      switch (i) {
        case 0: class_color = {255, 0, 0}; number << 1; break;
        case 1: class_color = {0, 0, 255}; number << 2; break;
        case 2: class_color = {255, 255, 0}; number << 3; break;
        case 3: class_color = {0, 255, 0}; number << 4; break;
      }
      render_text(prompt, {1020, y_location});
      location.y = y_location;
      SDL_Surface* message = TTF_RenderText_Solid(title_font_, number.str().c_str(), class_color);

      SDL_BlitSurface(message, nullptr, screen_, &location);
      SDL_FreeSurface( message );
      number.str(std::string());
      y_location += 122;
    }
  }
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

void Renderer::render_static_ui() {

  SDL_Rect src {0,0,220,56};
  SDL_Rect location {970, 10, 220, 56};
  SDL_BlitSurface(logo_, &src , screen_, &location);

  struct ClassInfo {
    std::string name;
    SDL_Color color;
    Sint16 x_location;
    Sint16 y_location;
  };

  // Define class names and their respective colors
  std::vector<ClassInfo> classes {
    {"Warrior", {255, 0, 0}, 1045, 150},
    {"Valkyrie", {0, 0, 255}, 1040, 272},
    {"Wizard", {255, 255, 0}, 1050, 394},
    {"Elf", {0, 255, 0}, 1080, 516}
  };

  // Render class names
  for (const auto& info : classes) {
    SDL_Surface* message = TTF_RenderText_Solid(title_font_, info.name.c_str(), info.color);
    SDL_Rect location = {info.x_location, info.y_location};
    SDL_BlitSurface(message, nullptr, screen_, &location);
    SDL_FreeSurface(message);
  }
}
