#include "Character.hpp"

#include <SDL/SDL.h>

Character::Character(SDL_Surface* spriteSheet, SDL_Surface* screen)
: move_up_(false), move_down_(false), move_left_(false), move_right_(false),
  screen_(screen), position_({0,0,0,0}), sprite_(spriteSheet) {
}

void Character::set_position(Sint16 x, Sint16 y){
  position_.x = x;
  position_.y = y;
}

void Character::render(){
  sprite_.render(screen_, position_.x, position_.y);
}