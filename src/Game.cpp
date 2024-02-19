#include "Game.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

Game::Game() 
  : m_screen(initScreen()), 
    m_spriteSheet(initSpriteSheet()), 
    m_player(m_spriteSheet, m_screen), 
    m_running(false)
{
  if (!m_spriteSheet) {
    // Sets screen to red on failure
    m_screenClearColor = SDL_MapRGB(m_screen->format, 255, 0, 0);
  } else {
    // Sets screen to green on success
    m_screenClearColor = SDL_MapRGB(m_screen->format, 66, 245, 203);
  }

  TTF_Init();
  m_font = TTF_OpenFont("<!Gauntlet$Dir>.Font", 28);
}

SDL_Surface* Game::initScreen() {
  // Initialization logic for screen
  return SDL_SetVideoMode(800, 600, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
}

SDL_Surface* Game::initSpriteSheet() {
  // Initialization logic for spriteSheet
  SDL_Surface* image = IMG_Load("<!Gauntlet$Dir>.entities");
  SDL_Surface* formattedImage = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  return formattedImage;
}

Game::~Game() {
  TTF_CloseFont( m_font );
  SDL_FreeSurface( m_spriteSheet );
  SDL_FreeSurface(m_screen);
  TTF_Quit();
  SDL_Quit();
}

void Game::handleEvents() {
  while (SDL_PollEvent(&m_event)) {
    if (m_event.type == SDL_QUIT || (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE)) {
      m_running = false;
    } else {
      m_player.handleInputs(m_event);
    }
  }
}

void Game::update() {
  m_player.update();
}

void Game::displayText(std::stringstream& messageString, SDL_Rect location) {
  SDL_Surface* message = TTF_RenderText_Solid(m_font, messageString.str().c_str(), m_textColor);

  SDL_FillRect(m_screen, nullptr, m_screenClearColor);
  SDL_BlitSurface(message, nullptr, m_screen, &location);
  SDL_Flip(m_screen);
  SDL_FreeSurface( message );
}

void Game::render() {
  // Clear screen
  SDL_FillRect(m_screen, nullptr, m_screenClearColor);

  m_player.render();

  // Update the screen    
  SDL_Flip(m_screen);
}

void Game::run() {

  m_running = true;

  m_player.setPosition(200,200);
  m_player.selectPlayerClass(PlayerClass::Wizard);

  // Game tick rate in ms, 20 ticks per second
  constexpr Uint32 dt {1000/20};

  // Time at the start of the last game loop
  Uint32 previous = SDL_GetTicks();

  // Discrepancy between game tick rate and frame rate
  Uint32 accumulator = 0;
  
  while (m_running) {
    Uint32 current = SDL_GetTicks();
    // Time the last frame took to render
    Uint32 frameTime = current - previous;
    previous = current;

    accumulator += frameTime;

    handleEvents();

    while(accumulator > dt) {
      update();
      accumulator -= dt;
    }

    render();
  }

  std::stringstream closingMessage;
  closingMessage << "Game Closing, time since elapsed : " << SDL_GetTicks();
  displayText(closingMessage, {150, 300});

  SDL_Delay(1000);
}