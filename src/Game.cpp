#include "Game.hpp"

#include <iostream>
#include <memory>

#include "GameManager.hpp"
#include "Models.hpp"
#include "Renderer.hpp"
#include "SDL/SDL_video.h"


Game::Game() 
  : renderer_(init_renderer()), 
    ui_manager_(std::make_shared<UIManager>()), 
    sound_manager_(std::make_shared<SoundManager>()), 
    game_manager_(std::make_shared<GameManager>()){
      subject_.addObserver(ui_manager_);
      subject_.addObserver(sound_manager_);
      subject_.addObserver(game_manager_);
}

Renderer Game::init_renderer() {

  SDL_Surface* screen =  SDL_SetVideoMode(1200, 640, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);

  // Initialization logic for screen
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.assets.entities");

  SDL_Surface* sprite_sheet = SDL_DisplayFormatAlpha(image);

  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.assets.title");

  SDL_Surface* formatted = SDL_DisplayFormat(image);
  
  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.assets.logo");

  SDL_Surface* logo = SDL_DisplayFormat(image);

  SDL_FreeSurface(image);

  image = IMG_Load("<!Gauntlet$Dir>.assets.key");

  SDL_Surface* key = SDL_DisplayFormatAlpha(image);


  return Renderer{sprite_sheet, screen, formatted, logo, key};
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
      notify(GameEvent::kMenu);
    } else {
      world.player_->handle_inputs(event_);
    }
  }
}

void Game::handle_menu_events(){
  while (SDL_PollEvent(&event_)) {
    if(event_.type == SDL_QUIT || (event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)){
      open_ = false;
      notify(GameEvent::kQuit);
    } else{
      if (event_.type == SDL_KEYDOWN) {
        switch (event_.key.keysym.sym) {
          case SDLK_1:
            ui_manager_->configure_player_class(PlayerClass::kWarrior);
            sound_manager_->configure_player_sounds(PlayerClass::kWarrior);
            notify(GameEvent::kGame);
            break;
          case SDLK_2:
            ui_manager_->configure_player_class(PlayerClass::kValkyrie);
            sound_manager_->configure_player_sounds(PlayerClass::kValkyrie);
            notify(GameEvent::kGame);
            break;
          case SDLK_3:
            ui_manager_->configure_player_class(PlayerClass::kWizard);
            sound_manager_->configure_player_sounds(PlayerClass::kWizard);
            notify(GameEvent::kGame);
            break;
          case SDLK_4:
            ui_manager_->configure_player_class(PlayerClass::kElf);
            sound_manager_->configure_player_sounds(PlayerClass::kElf);
            notify(GameEvent::kGame);
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

  for(const auto& door: world.doors_){
    renderer_.render(door);
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
  std::string level_name = game_manager_->load_level(world, *ui_manager_);
  
  if(level_name == "ended"){
    notify(GameEvent::KGameEnd);
    return;
  }

  SDL_Surface* image = IMG_Load(level_name.c_str());
  SDL_Surface* formatted_image = SDL_DisplayFormat(image);
  SDL_FreeSurface(image);

  renderer_.load_new_level(formatted_image);
}

void Game::run_game() {

  World world{ui_manager_->player_class_};

  // Add observers to player
  world.player_->addObserver(ui_manager_);
  world.player_->addObserver(sound_manager_);
  world.player_->addObserver(game_manager_);

  load_level(world);

  // Game tick rate in ms, 60 ticks per second
  constexpr Uint32 kTickRate {1000/60};

  // Time at the start of the last game loop
  Uint32 previous {SDL_GetTicks()};

  // Discrepancy between game tick rate and frame rate
  Uint32 accumulator {0};
  Uint32 current     {0};
  Uint32 frame_time  {0};
  
  while (game_manager_->running_) {

    if(game_manager_->level_exited){
      load_level(world);
      game_manager_->level_exited = false;
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
  
  // Start game with menu event
  notify(GameEvent::kMenu);
  while(open_){

    notify(GameEvent::kMenu);
    while(game_manager_->title_screen_){
      handle_menu_events();
      render_title();
    }

    if(game_manager_->running_){
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