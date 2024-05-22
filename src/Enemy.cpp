#include "Enemy.hpp"
#include "World.hpp"

int Enemy::ID = 0;

Enemy::Enemy(EnemyClass enemy_class, SDL_Rect position)
  :enemy_class_(enemy_class), standing_timer_(0) {
  switch (enemy_class) {
    case EnemyClass::kGhost:
      sprite_ = {SpriteClass::kGhost}; break;
    case EnemyClass::kDemon:
      sprite_ = {SpriteClass::kDemon}; break;
    case EnemyClass::kBoxer:
      sprite_ = {SpriteClass::kBoxer}; break;
    case EnemyClass::kDarkWizard:
      sprite_ = {SpriteClass::kDarkWizard}; break;
    case EnemyClass::kBlueGhost:
      sprite_ = {SpriteClass::kBlueGhost}; break;
  }
  position_ = position;
  last_position_ = position;
  sprite_.set_animation(AnimationState::kMovingRight);
  movespeed_ = 4;
  id_ = ID++;
};

void Enemy::death(){
  dying_ = true;
  sprite_.set_animation(AnimationState::kDeath);
};

void Enemy::move(int pixels, World& world) {

  // Calculate the difference in positions
  Sint16 dx = world.player_->position_.x - position_.x;
  Sint16 dy = world.player_->position_.y - position_.y;

  if (standing_timer_ != 0) {
    velocity_.x = dx;
    velocity_.y = dy;
    set_moving_animation();
    return;
  }

  if(blocked_){
    Uint32 current_time = SDL_GetTicks();
    // Only try unstuck every second
    if(current_time - last_stuck_attempt_ < 200){
      return;
    }

    last_stuck_attempt_ = current_time;
    int direction = rand() % 4;
    switch (direction) {
      case 0:
        velocity_.x = movespeed_;
        break;
      case 1:
        velocity_.x = -movespeed_;
        break;
      case 2:
        velocity_.y = movespeed_;
        break;
      case 3:
        velocity_.y = -movespeed_;
        break;
    }

    move_around_tiles(world, dy, dx);
    try_move(world, velocity_.x, velocity_.y);
    blocked_ = false;
    // Update animation based on velocity
    set_moving_animation();
    return;
  }

  // Calculate the magnitude of the difference
  float distance = std::sqrt(dx * dx + dy * dy);

  // Check if distance is non-zero before normalizing
  if (distance != 0) {

    // Set the velocity based on the direction and desired speed
    velocity_.x = (std::abs(dx) > 5) ? (dx > 0 ? movespeed_ : -movespeed_) : 0;
    velocity_.y = (std::abs(dy) > 5) ? (dy > 0 ? movespeed_ : -movespeed_) : 0;

  } else {
    // Handle the case where the player and the entity are at the same position
    // For example, set velocity to zero or take some other appropriate action
    velocity_.x = 0;
    velocity_.y = 0;
  }

  move_around_tiles(world, dy, dx);

  try_move(world, velocity_.x, velocity_.y);

  // Update animation based on velocity
  set_moving_animation();
}

bool Enemy::try_move(World& world, Sint16 vel_x, Sint16 vel_y) {

  // Check for collisions with other enemies
  for (auto& enemy : world.enemies_) {
    if (&enemy != this && !enemy.dying_ && check_collisions(*this, enemy, velocity_.x, velocity_.y)) {
      blocked_ = true;
      return false;
    }
  }

  // No collisions, update position and return true
  position_.x += velocity_.x;
  position_.y += velocity_.y;
  return true;
}

bool Enemy::check_collisions(Enemy& a, Enemy& b, Sint16 dx, Sint16 dy) {
  if (a.position_.x + dx + a.position_.w < b.position_.x ||
    a.position_.x + dx > b.position_.x + b.position_.w ||
    a.position_.y + dy + a.position_.h < b.position_.y ||
    a.position_.y + dy > b.position_.y + b.position_.h) {
    return false;
  }
  return true;
}

void Enemy::move_around_tiles(World& world, Sint16 dy, Sint16 dx){
  if (std::abs(dx) < 600 && std::abs(dy) < 400) {
    int tile_x = position_.x / 32;
    int tile_y = position_.y / 32;

    // Check the tiles directly adjacent to the enemy
    bool top_blocked = world.map_.tile_map[tile_y - 1][tile_x];
    bool top_right_blocked = !world.map_.tile_map[tile_y - 1][tile_x] & world.map_.tile_map[tile_y - 1][tile_x-1];
    bool top_left_blocked = !world.map_.tile_map[tile_y - 1][tile_x] & world.map_.tile_map[tile_y - 1][tile_x+1];
    bool left_top_blocked = !world.map_.tile_map[tile_y][tile_x-1] & world.map_.tile_map[tile_y+1][tile_x-1];
    bool bottom_blocked = world.map_.tile_map[tile_y + 1][tile_x];
    bool bottom_right_blocked = !world.map_.tile_map[tile_y+1][tile_x] & world.map_.tile_map[tile_y + 1][tile_x-1];
    bool bottom_left_blocked = !world.map_.tile_map[tile_y+1][tile_x] & world.map_.tile_map[tile_y + 1][tile_x+1];
    bool left_blocked = world.map_.tile_map[tile_y][tile_x - 1];
    bool right_blocked = world.map_.tile_map[tile_y][tile_x + 1]; 

    // Check if the enemy is moving horizontally and if the direction is blocked
    if (velocity_.x > 0 && right_blocked) velocity_.x = 0;
    if (velocity_.x < 0 && left_blocked) velocity_.x = 0;

    // Check if the enemy is moving vertically and if the direction is blocked
    if (velocity_.y > 0 && bottom_blocked) velocity_.y = 0;
    if (velocity_.y < 0 && top_blocked) velocity_.y = 0;

    // Stop getting stuck around corners
    if (velocity_.x < 0 && velocity_.y > 0 && bottom_left_blocked) velocity_.y = 0;
    if (velocity_.x < 0 && velocity_.y < 0 && top_left_blocked) velocity_.y = 0;
    if (velocity_.x < 0 && velocity_.y < 0 && left_top_blocked) velocity_.x = 0;

    if (velocity_.x > 0 && velocity_.y < 0 && top_right_blocked) velocity_.y = 0;
    if (velocity_.x > 0 && velocity_.y > 0 && bottom_right_blocked) velocity_.y = 0;

  }
}

void Enemy::set_moving_animation() {
  if (velocity_.x > 0) {
    if (velocity_.y > 0) {
      direction_ = Direction::kDownRight;
      sprite_.set_animation(AnimationState::kMovingDownRight);
      last_state_ = AnimationState::kIdleDownRight;
    } else if (velocity_.y < 0) {
      direction_ = Direction::kUpRight;
      sprite_.set_animation(AnimationState::kMovingUpRight);
      last_state_ = AnimationState::kIdleUpRight;
    } else {
      direction_ = Direction::kRight;
      sprite_.set_animation(AnimationState::kMovingRight);
      last_state_ = AnimationState::kIdleRight;
    }
  } else if (velocity_.x < 0) {
    if (velocity_.y > 0) {
      direction_ = Direction::kDownLeft;
      sprite_.set_animation(AnimationState::kMovingDownLeft);
      last_state_ = AnimationState::kIdleDownLeft;
    } else if (velocity_.y < 0) {
      direction_ = Direction::kUpLeft;
      sprite_.set_animation(AnimationState::kMovingUpLeft);
      last_state_ = AnimationState::kIdleUpLeft;
    } else {
      direction_ = Direction::kLeft;
      sprite_.set_animation(AnimationState::kMovingLeft);
      last_state_ = AnimationState::kIdleLeft;
    }
  } else {
    if (velocity_.y > 0) {
      direction_ = Direction::kDown;
      sprite_.set_animation(AnimationState::kMovingDown);
      last_state_ = AnimationState::kIdleDown;
    } else if (velocity_.y < 0) {
      direction_ = Direction::kUp;
      sprite_.set_animation(AnimationState::kMovingUp);
      last_state_ = AnimationState::kIdleUp;
    } else {
      sprite_.set_animation(last_state_);
    }
  }
}

void Enemy::update(World& world){

  if(dying_){
    sprite_.update();
    if(sprite_.ended_){
      dead_ = true;
    }
    return;
  }

  // If offscreen
  if(std::abs(world.player_->position_.x - position_.x) > 1000 && 
     std::abs(world.player_->position_.y - position_.y) > 700){
    sprite_.update();
    return;
  }

  last_position_ = position_;

  if (enemy_class_ == EnemyClass::kDemon || enemy_class_ == EnemyClass::kDarkWizard) {
    Uint32 current = SDL_GetTicks() - last_fire_;

    if(rand() % 100 <= 33 && current > 1000){
      firing_ = true;
    }

    // If the enemy is standing still, increment the standing timer
    if (firing_) {
      standing_timer_++;
    }

    // If the monster has stood still long enough they will fire and reset the standing timer
    if (standing_timer_ > standing_duration_){ 
      move(0, world);
      set_firing_animation();
      world.enemy_projectiles_.push_back(Projectile{position_, direction_, sprite_.sprite_class_, id_});
      firing_ = false;
      standing_timer_ = 0;
      last_fire_ = SDL_GetTicks();
    }
    else{
      move(movespeed_, world); 
    }

  } else {
    move(movespeed_, world); 

  }

  sprite_.update();
};