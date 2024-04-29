#include "Enemy.hpp"
#include "Sprite.hpp"

Enemy::Enemy(EnemyClass enemy_class)
  :enemy_class_(enemy_class){
};

// void Enemy::update(const Player& player){
//   // 25% chance the monster will stand still and fire a projectile if they can
//   // if(dist(engine) == 1 && (enemy_class_ == EnemyClass::kDemon || enemy_class_ == EnemyClass::kDarkWizard)){
//   //   // emit_projectile();
//   // }
//   // else{
    
//   // }
// }

void Enemy::update(World& world){
  sprite_.update();
};