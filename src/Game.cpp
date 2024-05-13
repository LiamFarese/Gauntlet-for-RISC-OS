#include "Game.hpp"
#include "Enemy.hpp"
#include "SDL/SDL.h"
#include <iostream>


Game::Game() 
  : running_(false),
    renderer_(init_renderer()) {;;
}

Renderer Game::init_renderer() {

  SDL_Surface* screen =  SDL_SetVideoMode(960, 640, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);

  // Initialization logic for screen
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");

  SDL_Surface* sprite_sheet = SDL_DisplayFormatAlpha(image);

  SDL_FreeSurface(image);

  return Renderer{sprite_sheet, screen};
}

Game::~Game() {
  renderer_.destory();
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

void Game::load_level(int level_id){
  std::string level_name {};
  switch(level_id){
    case (0):
      level_name = "<!Gauntlet$Dir>.training1";
      world_.load_level(0); 
      world_.player_->set_position(96,128);
      world_.player_->select_player_class(PlayerClass::kWizard);
      world_.player_->last_state_ = AnimationState::kIdleDown;
      Enemy enemy = {EnemyClass::kGhost, {400, 128}};
      world_.enemies_.push_back(enemy);
      break;
  }

  SDL_Surface* image = IMG_Load(level_name.c_str());

  SDL_Surface* formatted_image = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  renderer_.level_background_ = formatted_image;
}

void Game::render() {

  // Uint32 last_frame = SDL_GetTicks();

  renderer_.render_map(*world_.player_);
  
  renderer_.render(*world_.player_);

  for(const auto& enemy: world_.enemies_){
    renderer_.render(enemy);
  }

  for(const auto& p: world_.player_projectiles_){
    renderer_.render(p);
  }

  // std::stringstream frame_time;
  // frame_time << "frame time: " << SDL_GetTicks()-last_frame << "ms";
  // renderer_.render_text(frame_time, {700,0});

  // Update the screen   
  // renderer_.render_frame();
}

void Game::run() {

  running_ = true;

  load_level(0);

  // Game tick rate in ms, 20 ticks per second
  constexpr Uint32 kTickRate {1000/20};

  // Time at the start of the last game loop
  Uint32 previous {SDL_GetTicks()};

  // Discrepancy between game tick rate and frame rate
  Uint32 accumulator {0};
  Uint32 current     {0};
  Uint32 frame_time  {0};
  
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
    std::stringstream frame_time;
    frame_time << "frame time: " << SDL_GetTicks()-current << "ms";
    renderer_.render_text(frame_time, {700,0});
    renderer_.render_frame();
  }

  std::stringstream closing_message;
  closing_message << "Game Closing, time since elapsed : " << SDL_GetTicks();
  renderer_.render_text(closing_message, {150, 300});

  SDL_Delay(1000);
}