#include "SoundManager.hpp"
#include "Player.hpp"
#include "SDL/SDL_mixer.h"
#include <iostream>


SoundManager::SoundManager() {
  // Initialize SDL Mixer
  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0) {
    std::cout << "Failed to initialize SDL Mixer: " << Mix_GetError() << std::endl;
    }

  // Load background music
  background_music_ = Mix_LoadMUS("<!Gauntlet$Dir>.music.level_music_1");

  // Load menu sound
  menu_music_ = Mix_LoadMUS("<!Gauntlet$Dir>.music.menu_music_wav");
  if (!menu_music_) {
    std::cout << "Failed to load menu music: " << Mix_GetError() << std::endl;
  }

  // Load Sound effects
  monster_death_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.monster_death");
  collect_points_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.collect_points");
  level_exit_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.level_exit");
}

SoundManager::~SoundManager() {
  Mix_FreeMusic(menu_music_);
  menu_music_ = nullptr;

  Mix_FreeMusic(background_music_);
  background_music_ = nullptr;
  Mix_CloseAudio();
}

void SoundManager::configure_player_sounds(PlayerClass player){
  if(player == PlayerClass::kValkyrie){
    hurt_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.female_hurt");
  } else {
    hurt_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.male_hurt");
  }

  switch (player) {
    case PlayerClass::kWarrior: fire_sound_  = Mix_LoadWAV("<!Gauntlet$Dir>.music.warrior_fire"); break;
    case PlayerClass::kValkyrie: fire_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.valkyrie_fire"); break;
    case PlayerClass::kWizard: fire_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.wizard_fire"); break;
    case PlayerClass::kElf: fire_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.elf_fire"); break;
    default:
      break;
  }
}

void SoundManager::destroy(){
  this->~SoundManager();
}

void SoundManager::on_notify(GameEvent event){
  switch(event){
    case GameEvent::kPlayerDamage:
      play_sound(hurt_sound_);
      break;
    case GameEvent::kPlayerFire:
      play_sound(fire_sound_);
      break;
    case GameEvent::kEnemyDestroyed:
      play_sound(monster_death_);
      break;
    case GameEvent::kPointPickup:
      play_sound(collect_points_sound_);
      break;
    case GameEvent::kHealthPickup: 
      // TODO: implement health pickup
      break;
    case GameEvent::kHealthPotionPickup:
      // TODO: implement potions
      break;
    case GameEvent::kDestroyPotionPickup:
      // TODO: implement potions
      break;
    case GameEvent::kKeyPickup:
      // TODO: implement keys
      break;
    case GameEvent::kMenu:
      play_music(menu_music_);
      break;
    case GameEvent::kGame:
      play_music(background_music_);
      break;
    case GameEvent::kLevelExit:
      play_sound(level_exit_sound_);
      break;
    case GameEvent::kPlayerTickDamage:
      break;
    }
}

void SoundManager::play_music(Mix_Music* music){
  if (Mix_PlayMusic(music, -1) == -1) {
    // Handle music playing error
    std::cout << "Failed to play music: " << Mix_GetError() << '\n';
  }
}

void SoundManager::play_sound(Mix_Chunk* sound) {
  Mix_PlayChannel(-1, sound, 0);
}
