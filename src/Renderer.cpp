#include "Renderer.hpp"
#include "Player.hpp"
#include "SDL/SDL_stdinc.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_video.h"

// Used to display ui information
struct ClassInfo {
  std::string name;
  SDL_Color color;
  Sint16 x_location;
  Sint16 y_location;
};

Renderer::Renderer(SDL_Surface* sprite_sheet, SDL_Surface* screen, SDL_Surface* title_screen, 
                   SDL_Surface* logo, SDL_Surface* key)
  :sprite_sheet_(sprite_sheet), screen_(screen), title_screen_(title_screen), logo_(logo), key_(key) {
  TTF_Init();
  font_ = TTF_OpenFont("<!Gauntlet$Dir>.assets.Font", 20);
  title_font_ = TTF_OpenFont("<!Gauntlet$Dir>.assets.Font", 30);

};

Renderer::Renderer()
  : level_background_(nullptr),
    sprite_sheet_(nullptr),
    screen_(nullptr),
    font_(nullptr) {
}

Renderer::~Renderer() {
  if (sprite_sheet_) {
    SDL_FreeSurface(sprite_sheet_);
    sprite_sheet_ = nullptr;
  }

  if (screen_) {
    SDL_FreeSurface(screen_);
    screen_ = nullptr;
  }

  if (level_background_) {
    SDL_FreeSurface(level_background_);
    level_background_ = nullptr;
  }

  if (title_screen_) {
    SDL_FreeSurface(title_screen_);
    title_screen_ = nullptr;
  }

  if (logo_) {
    SDL_FreeSurface(logo_);
    logo_ = nullptr;
  }

  if (key_) {
    SDL_FreeSurface(key_);
    key_ = nullptr;
  }

  if (font_) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }

  if (title_font_) {
    TTF_CloseFont(title_font_);
    title_font_ = nullptr;
  }
}

void Renderer::destroy(){
  this->~Renderer();
}

void Renderer::clear(){
  SDL_FillRect(screen_, nullptr, screen_clear_color_);
}

void Renderer::render(const Door& door) const {
  SDL_Rect sprite = door.sprite;

  for(const auto& door_segment : door.location){
    SDL_Rect position = door_segment;
    position.x -= camera_.x;
    position.y -= camera_.y;
    SDL_BlitSurface(sprite_sheet_, &sprite, screen_, &position); 
  }
}

// Renders the level background
void Renderer::render_map(const Player& player) {
 // Calculate the center of the camera
  Sint16 camera_centre_x = camera_.x + camera_.w / 2;
  Sint16 camera_centre_y = camera_.y + camera_.h / 2;

  SDL_Rect player_position = player.get_position();
  // Calculate the offset of the player from the camera center
  Sint16 dx = player_position.x - camera_centre_x;
  Sint16 dy = player_position.y - camera_centre_y;

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


// Renders splash art
void Renderer::render_title() const{
  SDL_Rect position {0,0,960,640};
  SDL_Rect dest {0,0,960,640};
  SDL_BlitSurface(title_screen_, &position, screen_, &dest);

}

// Renders the entire sidebar
void Renderer::render_sidebar(UIManager& ui_manager) const {
  // Clear background and set it to black
  SDL_Rect ui {960, 0, 240, 640};
  SDL_FillRect(screen_, &ui, SDL_MapRGB(screen_->format, 0, 0, 0));

  render_static_ui();

  // Determine y-coordinate for health and score display based on player class
  Sint16 score_and_health_y = 0;
  switch(ui_manager.player_class_) {
    case PlayerClass::kWarrior: score_and_health_y = 222; break;
    case PlayerClass::kValkyrie: score_and_health_y = 344; break;
    case PlayerClass::kWizard: score_and_health_y = 466; break;
    case PlayerClass::kElf: score_and_health_y = 588; break;
    default: break;
  }

  std::string default_values = "000";
  if (ui_manager.game_running) {
    // Render level name
    std::stringstream title;
    title << ui_manager.level_name_;
    render_class_text(title, {1020,100}, {255,255,255});

    // Render the player's health and score
    render_text(ui_manager.health_str_, {1110, score_and_health_y});
    render_text(ui_manager.score_str_, {1030, score_and_health_y});

    render_keys(ui_manager, score_and_health_y);

    // Render default values for other classes
    Sint16 y_location = 222;
    for (int i = 0; i < 4; ++i) {
      render_text("health:", {1110, static_cast<Sint16>(y_location - 30)});
      render_text("score:", {1030, static_cast<Sint16>(y_location - 30)});
      if (i != static_cast<Sint16>(ui_manager.player_class_)) {
        render_text(default_values, {1110, y_location});
        render_text(default_values, {1030, y_location});
      }
      y_location += 122;
    }
  } else {
    // Game is not running, show prompt to press a key to play
    Sint16 y_location = 222;
    std::string prompt = "press          to play";
    SDL_Rect location {1075, 0, 0, 0}; // y will be set in the loop
    for (int i = 0; i < 4; ++i) {
      SDL_Color class_color;
      std::stringstream number;
      switch (i) {
        case 0: class_color = {255, 0, 0}; number << 1; break;
        case 1: class_color = {0, 0, 255}; number << 2; break;
        case 2: class_color = {255, 255, 0}; number << 3; break;
        case 3: class_color = {0, 255, 0}; number << 4; break;
      }
      render_text(prompt, {1020, y_location});
      location.y = y_location;
      render_class_text(number, location, class_color);
      number.str(std::string());
      y_location += 122;
    }
  }
}

// Renders text using the class colors and font size
void Renderer::render_class_text(const std::stringstream& message_string, SDL_Rect location, SDL_Color color) const {
  SDL_Surface* message = TTF_RenderText_Solid(title_font_, message_string.str().c_str(), color);
  SDL_BlitSurface(message, nullptr, screen_, &location);
  SDL_FreeSurface(message);
}

// Generic method for rendering standard white text
void Renderer::render_text(const std::string& message_string, SDL_Rect location) const {
  SDL_Surface* message = TTF_RenderText_Solid(font_, message_string.c_str(), text_color_);

  SDL_BlitSurface(message, nullptr, screen_, &location);
  SDL_FreeSurface( message );
}

// Called at the end of a frame to flip the buffer
void Renderer::render_frame() const {
  SDL_Flip(screen_);
}

void Renderer::load_new_level(SDL_Surface* level){
  SDL_FreeSurface(level_background_);
  level_background_ = level;
}


// Makes sure the frame returned by sprite.get_frame() is not empty
bool Renderer::is_zero(SDL_Rect& sprite) const {
  return sprite.h == 0 && sprite.w == 0;
}

// Used to determine if entity is offscreen, therefore skip rendering
bool Renderer::clip(SDL_Rect& location) const {
  return location.y > camera_.y + camera_.h ||
         location.x > camera_.x + camera_.w ||
         location.y + 32 < camera_.y ||
         location.x + 32 < camera_.x;
}

// Renders part of the ui that never changes
void Renderer::render_static_ui() const {

  // Render logo
  SDL_Rect src {0,0,220,56};
  SDL_Rect location {970, 10, 220, 56};
  SDL_BlitSurface(logo_, &src , screen_, &location);

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

void Renderer::render_keys(UIManager& ui_manager, Sint16 y_location) const {
  y_location += 20;
  SDL_Rect location {1050, y_location};

  for(int i = 0; i < ui_manager.keys_; i++){
    SDL_BlitSurface(key_, nullptr, screen_, &location);
    location.x += 30;
  }
}