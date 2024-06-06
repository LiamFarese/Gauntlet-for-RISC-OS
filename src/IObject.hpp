#pragma once

class World;

// Represents a game object
class IObject {

public:

  virtual void update(World& world) = 0;
};