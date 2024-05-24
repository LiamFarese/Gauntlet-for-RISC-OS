#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "Models.hpp"
#include "IObserver.hpp"
#include "Player.hpp"

class SoundManager : public IObserver {

public:

  SoundManager();
  ~SoundManager();

  void destroy();
  void configure_player_sounds(PlayerClass player_class_);

  void on_notify(GameEvent event);

private:

  // Background music
  Mix_Music* background_music_;
  Mix_Music* menu_music_;

  // Generics sounds
  Mix_Chunk* monster_death_;
  Mix_Chunk* collect_points_sound_;
  Mix_Chunk* collect_food_sound_;
  Mix_Chunk* level_exit_sound_;
  Mix_Chunk* collect_key_;
  Mix_Chunk* open_door_;

  // Player class dependant sounds
  Mix_Chunk* fire_sound_;
  Mix_Chunk* hurt_sound_;

  void play_music(Mix_Music* music);
  void play_sound(Mix_Chunk* sound);

};