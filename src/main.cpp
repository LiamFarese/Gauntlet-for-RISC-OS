#ifdef TEST

#include "../test/Player_test.cpp"
#include "../test/Projectile_test.cpp"

int main() {  
  
  test_player_initialization();
  test_player_movement();
  test_player_damage();
  test_player_pickup_item();
  test_player_open_door();
  test_player_observer();
  test_projectile_creation();
  test_projectile_movement();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}

#else

#include <memory.h>
#include "Application.hpp"

int main(int argc, char* args[]) {
  Application application;
  application.run();
  return 0;
}

#endif
