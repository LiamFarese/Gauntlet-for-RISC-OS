#pragma once

#include "Models.hpp"

class IObserver {
public:
  virtual ~IObserver() {}
  virtual void on_notify(GameEvent event) = 0;
};