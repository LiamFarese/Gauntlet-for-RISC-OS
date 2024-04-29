#include "Game.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Sprite.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

Game::Game() 
  : screen_(init_screen()), 
    sprite_sheet_(init_sprite_sheet()),
    background_(init_background()),
    renderer(sprite_sheet_, background_, screen_),
    running_(false) {

  if (!sprite_sheet_) {
    // Sets screen to red on failure
    screen_clear_color_ = SDL_MapRGB(screen_->format, 255, 0, 0);
  } else {
    // Sets screen to green on success
    screen_clear_color_ = SDL_MapRGB(screen_->format, 66, 245, 203);
  }

  TTF_Init();
  font_ = TTF_OpenFont("<!Gauntlet$Dir>.Font", 28);
}

SDL_Surface* Game::init_screen() {
  // Initialization logic for screen
  return SDL_SetVideoMode(960, 960, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
}

SDL_Surface* Game::init_sprite_sheet() {
  // Initialization logic for spriteSheet
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");
  SDL_Surface* formatted_image = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  return formatted_image;
}

SDL_Surface* Game::init_background() {
  // Initialization logic for spriteSheet
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.background");
  SDL_Surface* formatted_image = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  return formatted_image;
}

Game::~Game() {
  TTF_CloseFont(font_);
  SDL_FreeSurface(sprite_sheet_);
  SDL_FreeSurface(screen_);
  TTF_Quit();
  SDL_Quit();
}

void Game::handle_events() {
  while (SDL_PollEvent(&event_)) {
    if (event_.type == SDL_QUIT || (event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)) {
      running_ = false;
    } else {
      world_.player_->handle_inputs(event_);
    }
  }
}

void Game::display_text(std::stringstream& message_string, SDL_Rect location) {
  SDL_Surface* message = TTF_RenderText_Solid(font_, message_string.str().c_str(), text_color_);

  SDL_FillRect(screen_, nullptr, screen_clear_color_);
  SDL_BlitSurface(message, nullptr, screen_, &location);
  SDL_Flip(screen_);
  SDL_FreeSurface( message );
}

void Game::render() {
  // Clear screen
  SDL_FillRect(screen_, nullptr, screen_clear_color_);

  renderer.render(world_.map_);
  renderer.render(*world_.player_);

  for(const auto& enemy: world_.enemies_){
    renderer.render(enemy);
  }

  for(const auto& p: world_.player_projectiles_){
    renderer.render(p);
  }
  
  // Update the screen    
  SDL_Flip(screen_);
}

void Game::run() {

  running_ = true;

  world_.player_->set_position(200,200);
  world_.player_->select_player_class(PlayerClass::kElf);
  world_.player_->last_state_ = AnimationState::kIdleDown;
  world_.load_level(1);

  // Game tick rate in ms, 20 ticks per second
  constexpr Uint32 kTickRate {1000/20};

  // Time at the start of the last game loop
  Uint32 previous {SDL_GetTicks()};

  // Discrepancy between game tick rate and frame rate
  Uint32 accumulator {0};
  Uint32 current {};
  Uint32 frame_time {};
  
  while (running_) {
    current = SDL_GetTicks();
    // Time the last frame took to render
    frame_time = current - previous;
    previous = current;

    accumulator += frame_time;

    handle_events();

    while(accumulator > kTickRate) {
      world_.update();
      accumulator -= kTickRate;
    }

    render();
  }

  std::stringstream closing_message;
  closing_message << "Game Closing, time since elapsed : " << SDL_GetTicks();
  display_text(closing_message, {150, 300});

  SDL_Delay(1000);
}