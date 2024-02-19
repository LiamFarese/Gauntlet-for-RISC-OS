#include "Character.hpp"

#include <SDL/SDL.h>

Character::Character(SDL_Surface* spriteSheet, SDL_Surface* screen)
: m_moveUp(false), m_moveDown(false), m_moveLeft(false), m_moveRight(false),
  m_screen(screen), m_position({0,0,0,0}), m_sprite(spriteSheet) {
}

void Character::setPosition(int x, int y){
  m_position.x = x;
  m_position.y = y;
}

void Character::render(){
  m_sprite.render(m_screen, m_position.x, m_position.y);
}