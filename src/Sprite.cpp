#include "Sprite.hpp"
#include "SDL/SDL.h"

Sprite::Sprite(SDL_Surface* spriteSheet) 
  : m_spriteSheet(spriteSheet) {
}

void Sprite::addAnimation(AnimationState state, std::vector<SpriteIndex> frames){
  m_animations[state] = frames;
}

void Sprite::setAnimation(AnimationState state){
  if (m_currentState != state) {
    m_currentState = state;
    m_currentFrames = &m_animations[state];
    m_currentFrame = 0; // Reset to the first frame
  }
}

void Sprite::setSpriteClass(SpriteClass spriteClass){
  m_spriteClass = spriteClass;
}

void Sprite::update(){
  Uint32 frameTime = SDL_GetTicks() - m_lastFrameTime;
  if (m_currentFrames && !m_currentFrames->empty() && frameTime > 50) {
    m_currentFrame = (m_currentFrame + 1) % m_currentFrames->size();
    m_lastFrameTime = SDL_GetTicks();
  }
}

void Sprite::render(SDL_Surface* targetSurface, int x, int y){
  if (m_currentFrames && !m_currentFrames->empty()) {
    SpriteIndex& point = (*m_currentFrames)[m_currentFrame];
    SDL_Rect frame = {point, static_cast<Sint16>(m_spriteClass), 32, 32};
    SDL_Rect destRect = {static_cast<Sint16>(x), static_cast<Sint16>(y), 32, 32};
    SDL_BlitSurface(m_spriteSheet, &frame, targetSurface, &destRect);
  }
}
 