#include "Game.hpp"


Game::Game() 
  : renderer_(init_renderer()) {;;
}

Renderer Game::init_renderer() {

  SDL_Surface* screen =  SDL_SetVideoMode(1200, 640, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);

  // Initialization logic for screen
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");

  SDL_Surface* sprite_sheet = SDL_DisplayFormatAlpha(image);

  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.title");

  SDL_Surface* formatted = SDL_DisplayFormat(image);

  return Renderer{sprite_sheet, screen, formatted};
}

Game::~Game() {
  renderer_.destory();
  TTF_Quit();
  SDL_Quit();
}

void Game::handle_game_events(World& world) {
  while (SDL_PollEvent(&event_)) {
  
    if (event_.type == SDL_QUIT || (event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)) {
      running_ = false;
      title_screen_ = true;
    } else {
      world.player_->handle_inputs(event_);
    }
  }
}

void Game::handle_menu_events(){
  while (SDL_PollEvent(&event_)) {
    if(event_.type == SDL_QUIT || (event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)){
      open_ = false;
      title_screen_ = false;
    } else{
        if (event_.type == SDL_KEYDOWN) {
          switch (event_.key.keysym.sym) {
            case SDLK_1:
              selected_class_ = PlayerClass::kWarrior; 
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_2:
              selected_class_ = PlayerClass::kValkyrie;
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_3:
              selected_class_ = PlayerClass::kWizard;
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_4:
              selected_class_ = PlayerClass::kElf; 
              running_ = true; 
              title_screen_ = false; 
              break;
            default: break;
          }
        }
    }
  } 
}

void Game::render(World& world) {

  // Uint32 last_frame = SDL_GetTicks();

  renderer_.render_map(*world.player_);
  
  renderer_.render(*world.player_);

  for(const auto& enemy: world.enemies_){
    renderer_.render(enemy);
  }

  for(const auto& p: world.player_projectiles_){
    renderer_.render(p);
  }

  for(const auto& p: world.enemy_projectiles_){
    renderer_.render(p);
  }

  renderer_.render_sidebar();
  std::stringstream ss;
  ss << "health: " << world.player_->health_;
  std::string healthText = ss.str();
  renderer_.render_text(healthText, {700,0});

  // Update the screen   
  renderer_.render_frame();
}

void Game::render_title(){
  renderer_.render_title();
  renderer_.render_frame();
}

void Game::load_level(World& world, int level_id){
  std::string level_name {};
  switch(level_id){
    case (0):
      world.load_level(0); 
      level_name = world.map_.level_name;
      break;
  }

  SDL_Surface* image = IMG_Load(level_name.c_str());

  SDL_Surface* formatted_image = SDL_DisplayFormat(image);
  SDL_FreeSurface(image);
  renderer_.level_background_ = formatted_image;
}

void Game::run_game() {

  World world{selected_class_};
  load_level(world, 0);

  // Game tick rate in ms, 30 ticks per second
  constexpr Uint32 kTickRate {1000/30};

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

    handle_game_events(world);

    while(accumulator > kTickRate) {
      world.update(renderer_.camera_);
      accumulator -= kTickRate;
    }

    render(world);
  }
}

void Game::start(){
  // Random number generator used in enemy AI
  srand(time(NULL));

  title_screen_ = true;
  while(open_){
    while(title_screen_){
      handle_menu_events();
      render_title();
    }

    if(running_){
      run_game();
    }
  }

  renderer_.clear();
  std::stringstream closing_message;
  closing_message << "Game Closing, time since elapsed : " << SDL_GetTicks();
  renderer_.render_text(closing_message.str(), {150, 300});
  renderer_.render_frame();
  SDL_Delay(1000);
}