#include "World.hpp"

World::World() {
  player_ = new Player();
}

World::~World() {
  delete player_;
}

void World::update() {
  player_->update(*this);

  for(auto& enemy: enemies_){
    enemy.update(*this);
  }
  for(auto& projectile: player_projectiles_){
    projectile.update();
  }

  for(auto& projectile: enemy_projectiles_){
    projectile.update();
  }
}