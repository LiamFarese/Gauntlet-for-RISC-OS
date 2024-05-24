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
  collect_food_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.collectfood");
  level_exit_sound_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.level_exit");
  collect_key_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.collectkey");
  open_door_ = Mix_LoadWAV("<!Gauntlet$Dir>.music.opendoor");
}

SoundManager::~SoundManager() {
  // Free music
  if (menu_music_) {
    Mix_FreeMusic(menu_music_);
    menu_music_ = nullptr;
  }

  if (background_music_) {
    Mix_FreeMusic(background_music_);
    background_music_ = nullptr;
  }

  // Free sound effects
  if (monster_death_) {
    Mix_FreeChunk(monster_death_);
    monster_death_ = nullptr;
  }

  if (collect_points_sound_) {
    Mix_FreeChunk(collect_points_sound_);
    collect_points_sound_ = nullptr;
  }

  if (collect_food_sound_) {
    Mix_FreeChunk(collect_food_sound_);
    collect_food_sound_ = nullptr;
  }

  if (level_exit_sound_) {
    Mix_FreeChunk(level_exit_sound_);
    level_exit_sound_ = nullptr;
  }
  
  if (collect_key_) {
    Mix_FreeChunk(collect_key_);
    collect_key_ = nullptr;
  }

  if (open_door_) {
    Mix_FreeChunk(open_door_);
    collect_key_ = nullptr;
  }

  // Close SDL Mixer
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
      play_sound(collect_food_sound_);
      break;
    case GameEvent::kHealthPotionPickup:
      // TODO: implement potions
      break;
    case GameEvent::kDestroyPotionPickup:
      // TODO: implement potions
      break;
    case GameEvent::kKeyPickup:
      play_sound(collect_key_);
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
      // No case
      break;
    case GameEvent::KGameEnd:
      play_music(menu_music_);
      break;
    case GameEvent::kPlayerDeath:
      // TODO: death sound
      break;
    case GameEvent::kQuit:
      break;
    case GameEvent::kOpenDoor:
      play_sound(open_door_);
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
