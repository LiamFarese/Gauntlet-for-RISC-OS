#pragma once

#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Player.hpp"

class Game {

public:

  Game();

  ~Game();

  void run();

private:
  SDL_Surface* m_screen;
  SDL_Surface* m_spriteSheet;
  Player m_player;

  Uint32 m_screenClearColor;
  SDL_Color m_textColor { 255, 255, 255 };
  TTF_Font* m_font;
  
  bool m_running;
  SDL_Event m_event;

  void handleEvents();

  void update();

  void displayText(std::stringstream& messageString, SDL_Rect location);

  void render();

  // Helper methods for initialization
  SDL_Surface* initScreen();
  SDL_Surface* initSpriteSheet();

};