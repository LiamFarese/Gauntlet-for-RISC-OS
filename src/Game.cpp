#include "Game.hpp"


Game::Game() 
  : running_(false),
    renderer(init_renderer()) {
}

Renderer Game::init_renderer() {
  // Initialization logic for screen
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");
  SDL_Surface* sprite_sheet = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);

  SDL_Surface* screen =  SDL_SetVideoMode(960, 640, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);

  return {sprite_sheet, screen};
}

Game::~Game() {
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
      level_name = "<!Gauntlet$Dir>.training1"; break;
  }
  SDL_Surface* image = IMG_Load(level_name.c_str());

  SDL_Surface* formatted_image = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  renderer.level_background_ = formatted_image;

  world_.player_->select_player_class(PlayerClass::kElf);
  world_.player_->last_state_ = AnimationState::kIdleDown;
  world_.load_level(level_id);
}

void Game::render() {

  Uint32 last_frame = SDL_GetTicks();

  // Clear screen
  renderer.clear();

  renderer.render_map();

  renderer.render(*world_.player_);

  for(const auto& enemy: world_.enemies_){
    renderer.render(enemy);
  }

  for(const auto& p: world_.player_projectiles_){
    renderer.render(p);
  }

  std::stringstream frame_time;
  frame_time << "frame time: " << SDL_GetTicks()-last_frame << "ms";
  renderer.render_text(frame_time, {700,0});

  // Update the screen    
  renderer.render_frame();
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
  }

  std::stringstream closing_message;
  closing_message << "Game Closing, time since elapsed : " << SDL_GetTicks();
  renderer.render_text(closing_message, {150, 300});

  SDL_Delay(1000);
}