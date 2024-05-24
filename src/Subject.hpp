#pragma once

#include <memory>
#include <vector>

#include "IObserver.hpp"

class Subject {

public:

  Subject();

  void addObserver(std::shared_ptr<IObserver> observer);
  void removeObserver(std::shared_ptr<IObserver> observer);
  void notify(GameEvent event);

private:
  std::vector<std::shared_ptr<IObserver>> observers_;
};
