#include "Enemy.hpp"
#include "Models.hpp"
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
  actor_.position_ = position;
  actor_.last_position_ = position;
  sprite_.set_animation(AnimationState::kMovingRight);
  actor_.movespeed_ = 2;
  id_ = ID++;
};

void Enemy::death(){
  actor_.dying_ = true;
  sprite_.set_animation(AnimationState::kDeath);
};

void Enemy::move(int pixels, World& world) {

  SDL_Rect player_position = world.player_->get_position();
  
  // Calculate the difference in positions
  Sint16 dx = player_position.x - actor_.position_.x;
  Sint16 dy = player_position.y - actor_.position_.y;

  if (standing_timer_ != 0) {
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
        actor_.velocity_.x = actor_.movespeed_;
        break;
      case 1:
        actor_.velocity_.x = -actor_.movespeed_;
        break;
      case 2:
        actor_.velocity_.y = actor_.movespeed_;
        break;
      case 3:
        actor_.velocity_.y = -actor_.movespeed_;
        break;
    }

    move_around_tiles(world, dy, dx);
    try_move(world, actor_.velocity_.x, actor_.velocity_.y);
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
    actor_.velocity_.x = (std::abs(dx) > 5) ? (dx > 0 ? actor_.movespeed_ : -actor_.movespeed_) : 0;
    actor_.velocity_.y = (std::abs(dy) > 5) ? (dy > 0 ? actor_.movespeed_ : -actor_.movespeed_) : 0;

  } else {
    // Handle the case where the player and the entity are at the same position
    // For example, set velocity to zero or take some other appropriate action
    actor_.velocity_.x = 0;
    actor_.velocity_.y = 0;
  }

  move_around_tiles(world, dy, dx);

  try_move(world, actor_.velocity_.x, actor_.velocity_.y);

  // Update animation based on velocity
  set_moving_animation();
}

bool Enemy::try_move(World& world, Sint16 vel_x, Sint16 vel_y) {

  // Check for collisions with other enemies
  for (auto& enemy : world.enemies_) {
    if (&enemy != this && !enemy.actor_.dying_ && check_collisions(*this, enemy, actor_.velocity_.x, actor_.velocity_.y)) {
      blocked_ = true;
      return false;
    }
  }

  // No collisions, update position and return true
  actor_.position_.x += actor_.velocity_.x;
  actor_.position_.y += actor_.velocity_.y;
  return true;
}

bool Enemy::check_collisions(Enemy& a, Enemy& b, Sint16 dx, Sint16 dy) {
  if (a.actor_.position_.x + dx + a.actor_.position_.w < b.actor_.position_.x ||
    a.actor_.position_.x + dx > b.actor_.position_.x + b.actor_.position_.w ||
    a.actor_.position_.y + dy + a.actor_.position_.h < b.actor_.position_.y ||
    a.actor_.position_.y + dy > b.actor_.position_.y + b.actor_.position_.h) {
    return false;
  }
  return true;
}

void Enemy::move_around_tiles(World& world, Sint16 dy, Sint16 dx){
  if (std::abs(dx) < 600 && std::abs(dy) < 400) {
    // Each tile is 32*32 pixels
    int tile_x = actor_.position_.x / 32;
    int tile_y = actor_.position_.y / 32;

    // Check the tiles directly adjacent to the enemy
    bool top_blocked = world.tile_map_[tile_y - 1][tile_x];
    bool top_right_blocked = !world.tile_map_[tile_y - 1][tile_x] & world.tile_map_[tile_y - 1][tile_x-1];
    bool top_left_blocked = !world.tile_map_[tile_y - 1][tile_x] & world.tile_map_[tile_y - 1][tile_x+1];
    bool left_top_blocked = !world.tile_map_[tile_y][tile_x-1] & world.tile_map_[tile_y+1][tile_x-1];
    bool right_bottom_blocked = !world.tile_map_[tile_y][tile_x+1] & world.tile_map_[tile_y-1][tile_x+1];
    bool bottom_blocked = world.tile_map_[tile_y + 1][tile_x];
    bool bottom_right_blocked = !world.tile_map_[tile_y+1][tile_x] & world.tile_map_[tile_y + 1][tile_x-1];
    bool bottom_left_blocked = !world.tile_map_[tile_y+1][tile_x] & world.tile_map_[tile_y + 1][tile_x+1];
    bool left_blocked = world.tile_map_[tile_y][tile_x - 1];
    bool right_blocked = world.tile_map_[tile_y][tile_x + 1]; 

    // Check if the enemy is moving horizontally and if the direction is blocked
    if (actor_.velocity_.x > 0 && right_blocked) actor_.velocity_.x = 0;
    if (actor_.velocity_.x < 0 && left_blocked) actor_.velocity_.x = 0;

    // Check if the enemy is moving vertically and if the direction is blocked
    if (actor_.velocity_.y > 0 && bottom_blocked) actor_.velocity_.y = 0;
    if (actor_.velocity_.y < 0 && top_blocked) actor_.velocity_.y = 0;

    // Stop getting stuck around corners
    if (actor_.velocity_.x < 0 && actor_.velocity_.y > 0 && bottom_left_blocked) actor_.velocity_.y = 0;
    if (actor_.velocity_.x < 0 && actor_.velocity_.y < 0 && top_left_blocked) actor_.velocity_.y = 0;
    if (actor_.velocity_.x < 0 && actor_.velocity_.y < 0 && left_top_blocked) actor_.velocity_.x = 0;
    if (actor_.velocity_.x > 0 && actor_.velocity_.y > 0 && right_bottom_blocked) actor_.velocity_.x = 0;
    if (actor_.velocity_.x > 0 && actor_.velocity_.y < 0 && top_right_blocked) actor_.velocity_.y = 0;
    if (actor_.velocity_.x > 0 && actor_.velocity_.y > 0 && bottom_right_blocked) actor_.velocity_.y = 0;

  }
}

void Enemy::set_moving_animation() {
  if (actor_.velocity_.x > 0) {
    if (actor_.velocity_.y > 0) {
      actor_.direction_ = Direction::kDownRight;
      sprite_.set_animation(AnimationState::kMovingDownRight);
      actor_.last_state_ = AnimationState::kIdleDownRight;
    } else if (actor_.velocity_.y < 0) {
      actor_.direction_ = Direction::kUpRight;
      sprite_.set_animation(AnimationState::kMovingUpRight);
      actor_.last_state_ = AnimationState::kIdleUpRight;
    } else {
      actor_.direction_ = Direction::kRight;
      sprite_.set_animation(AnimationState::kMovingRight);
      actor_.last_state_ = AnimationState::kIdleRight;
    }
  } else if (actor_.velocity_.x < 0) {
    if (actor_.velocity_.y > 0) {
      actor_.direction_ = Direction::kDownLeft;
      sprite_.set_animation(AnimationState::kMovingDownLeft);
      actor_.last_state_ = AnimationState::kIdleDownLeft;
    } else if (actor_.velocity_.y < 0) {
      actor_.direction_ = Direction::kUpLeft;
      sprite_.set_animation(AnimationState::kMovingUpLeft);
      actor_.last_state_ = AnimationState::kIdleUpLeft;
    } else {
      actor_.direction_ = Direction::kLeft;
      sprite_.set_animation(AnimationState::kMovingLeft);
      actor_.last_state_ = AnimationState::kIdleLeft;
    }
  } else {
    if (actor_.velocity_.y > 0) {
      actor_.direction_ = Direction::kDown;
      sprite_.set_animation(AnimationState::kMovingDown);
      actor_.last_state_ = AnimationState::kIdleDown;
    } else if (actor_.velocity_.y < 0) {
      actor_.direction_ = Direction::kUp;
      sprite_.set_animation(AnimationState::kMovingUp);
      actor_.last_state_ = AnimationState::kIdleUp;
    } else {
      sprite_.set_animation(actor_.last_state_);
    }
  }
}

void Enemy::update(World& world){

  if(actor_.dying_){
    sprite_.update();
    if(sprite_.ended_){
      actor_.dead_ = true;
    }
    return;
  }

  SDL_Rect player_position = world.player_->get_position();

  // If offscreen
  if(std::abs(player_position.x - actor_.position_.x) > 700 && 
     std::abs(player_position.y - actor_.position_.y) > 400){
    sprite_.update();
    return;
  }

  actor_.last_position_ = actor_.position_;

  if (enemy_class_ == EnemyClass::kDemon || enemy_class_ == EnemyClass::kDarkWizard) {
    Uint32 current = SDL_GetTicks() - actor_.last_fire_;

    bool firing_distance = std::abs(player_position.x - actor_.position_.x) < 500 && 
                           std::abs(player_position.y - actor_.position_.y) < 500;

    if (rand() % 100 <= 33 && current > static_cast<Uint32>(1000 + rand() % 500) && firing_distance) {
        actor_.firing_ = true;
    }

    // If the enemy is standing still, increment the standing timer
    if (actor_.firing_) {
      standing_timer_++;
    }

    // If the monster has stood still long enough they will fire and reset the standing timer
    if (standing_timer_ > standing_duration_){ 
      move(0, world);
      sprite_.set_firing_animation(actor_.direction_);
      world.enemy_projectiles_.push_back(Projectile{actor_.position_, actor_.direction_, sprite_.sprite_class_, id_});
      actor_.firing_ = false;
      standing_timer_ = 0;
      actor_.last_fire_ = SDL_GetTicks();
    }
    else{
      move(actor_.movespeed_, world); 
    }

  } else {
    move(actor_.movespeed_, world); 

  }

  sprite_.update();
};