#ifdef RUNNING_TESTS

#include <iostream>
#include <cassert>

#include "../src/Player.hpp"
#include "../src/World.hpp"
#include "../src/Models.hpp"

// Mock classes to replace complex dependencies
class MockWorld : public World {
    // Implement necessary methods or leave them empty if not needed for the test
};

class MockObserver : public IObserver {
public:
    void on_notify(GameEvent event) override {
      notified = true;
      lastEvent = event;
    }
    
    bool notified = false;
    GameEvent lastEvent;
};

void test_player_initialization() {
    Player player{PlayerClass::kWarrior};
    assert(player.get_position().x == 0);
    assert(player.get_position().y == 0);
    std::cout << "Player initialization test passed." << std::endl;
}

void test_player_movement() {
    Player player{PlayerClass::kWarrior};
    player.set_position(10, 10);
    assert(player.get_position().x == 10);
    assert(player.get_position().y == 10);
    player.set_position({20, 20, 0, 0});
    assert(player.get_position().x == 20);
    assert(player.get_position().y == 20);
    std::cout << "Player movement test passed." << std::endl;
}

void test_player_damage() {
    Player player{PlayerClass::kWarrior};
    int initial_health = player.get_health();
    player.damage();
    assert(player.get_health() == initial_health - player.get_damage_per_hit());
    std::cout << "Player damage test passed." << std::endl;
}

void test_player_pickup_item() {
    Player player{PlayerClass::kWarrior};
    int initial_health = player.get_health();
    Pickup healthPickup{PickupType::kHealth, {0,0,0,0}};
    player.pickup_item(healthPickup);
    assert(player.get_health() > initial_health); // Assuming health pickup increases health
    std::cout << "Player pickup item test passed." << std::endl;
}

void test_player_open_door() {
    Player player{PlayerClass::kWarrior};
    Pickup key{PickupType::kKey, {0,0,0,0}};
    player.pickup_item(key);
    assert(player.open_door() == true);
    assert(player.get_keys() == 0);
    assert(player.open_door() == false);
    std::cout << "Player open door test passed." << std::endl;
}

void test_player_observer() {
    Player player{PlayerClass::kWarrior};
    auto observer = std::make_shared<MockObserver>();
    player.addObserver(observer);
    player.notify(GameEvent::kHealthPickup);
    assert(observer->notified == true);
    assert(observer->lastEvent == GameEvent::kHealthPickup);
    std::cout << "Player observer test passed." << std::endl;
}

#endif
