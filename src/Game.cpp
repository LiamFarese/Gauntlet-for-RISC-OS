#include "Game.hpp"

#include <iostream>
#include <memory>

Game::Game() 
  : renderer_(init_renderer()), 
    ui_manager_(std::make_shared<UIManager>()), 
    sound_manager_(std::make_shared<SoundManager>()), 
    level_manager_(std::make_shared<LevelManager>()){
      subject_.addObserver(ui_manager_);
      subject_.addObserver(sound_manager_);
      subject_.addObserver(level_manager_);
}

Renderer Game::init_renderer() {

  SDL_Surface* screen =  SDL_SetVideoMode(1200, 640, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);

  // Initialization logic for screen
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");

  SDL_Surface* sprite_sheet = SDL_DisplayFormatAlpha(image);

  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.title");

  SDL_Surface* formatted = SDL_DisplayFormat(image);
  
  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.logo");

  SDL_Surface* logo = SDL_DisplayFormat(image);

  SDL_FreeSurface(image);

  return Renderer{sprite_sheet, screen, formatted, logo};
}

Game::~Game() {
  renderer_.destroy();
  sound_manager_->destroy();
  TTF_Quit();
  SDL_Quit();
}

void Game::handle_game_events(World& world) {
  while (SDL_PollEvent(&event_)) {
  
    if (event_.type == SDL_QUIT || (event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)) {
      ui_manager_->game_running  = false;
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
              ui_manager_->configure_player_class(PlayerClass::kWarrior);
              sound_manager_->configure_player_sounds(PlayerClass::kWarrior);
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_2:
              ui_manager_->configure_player_class(PlayerClass::kValkyrie);
              sound_manager_->configure_player_sounds(PlayerClass::kValkyrie);
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_3:
              ui_manager_->configure_player_class(PlayerClass::kWizard);
              sound_manager_->configure_player_sounds(PlayerClass::kWizard);
              running_ = true;
              title_screen_ = false; 
              break;
            case SDLK_4:
              ui_manager_->configure_player_class(PlayerClass::kElf);
              sound_manager_->configure_player_sounds(PlayerClass::kElf);
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

  for(const auto& p : world.pickups_){
    renderer_.render(p);
  }

  renderer_.render_sidebar(*ui_manager_);

  // Update the screen   
  renderer_.render_frame();
}

void Game::render_title() {
  renderer_.render_title();
  renderer_.render_sidebar(*ui_manager_);
  renderer_.render_frame();
}

void Game::load_level(World& world){
  std::string level_name = level_manager_->load_level(world, *ui_manager_);

  SDL_Surface* image = IMG_Load(level_name.c_str());

  SDL_Surface* formatted_image = SDL_DisplayFormat(image);
  SDL_FreeSurface(image);
  renderer_.level_background_ = formatted_image;
}

void Game::run_game() {

  notify(GameEvent::kGame);

  World world{ui_manager_->player_class_};

  // Add observers to player
  world.player_->subject_.addObserver(ui_manager_);
  world.player_->subject_.addObserver(sound_manager_);
  world.player_->subject_.addObserver(level_manager_);

  load_level(world);

  // Game tick rate in ms, 30 ticks per second
  constexpr Uint32 kTickRate {1000/60};

  // Time at the start of the last game loop
  Uint32 previous {SDL_GetTicks()};

  // Discrepancy between game tick rate and frame rate
  Uint32 accumulator {0};
  Uint32 current     {0};
  Uint32 frame_time  {0};
  
  while (running_) {

    if(level_manager_->level_exited){
      load_level(world);
      level_manager_->level_exited = false;
    }

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
    notify(GameEvent::kMenu);
    std::cout << level_manager_->level_id << '\n';
    std::cout << level_manager_->level_exited << '\n';

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

void Game::notify(GameEvent event){
  subject_.notify(event);
}