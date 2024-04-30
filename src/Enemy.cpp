#include "Enemy.hpp"
#include "Sprite.hpp"

Enemy::Enemy(EnemyClass enemy_class, SDL_Rect position)
  :enemy_class_(enemy_class){
    switch (enemy_class) {
      case EnemyClass::kGhost:
        sprite_.sprite_class_ = SpriteClass::kGhost; break;
      case EnemyClass::kDemon:
        sprite_.sprite_class_ = SpriteClass::kDemon; break;
      case EnemyClass::kBoxer:
        sprite_.sprite_class_ = SpriteClass::kBoxer; break;
      case EnemyClass::kDarkWizard:
        sprite_.sprite_class_ = SpriteClass::kDarkWizard; break;
      case EnemyClass::kBlueGhost:
        sprite_.sprite_class_ = SpriteClass::kBlueGhost; break;
    }
    position_ = position;
    sprite_.set_animation(AnimationState::kIdleDown);
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
  last_position_ = position_;
  sprite_.update();
};