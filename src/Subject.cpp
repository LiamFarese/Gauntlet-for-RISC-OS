#include "Subject.hpp"

#include <algorithm>

Subject::Subject() {
}

void Subject::addObserver(std::shared_ptr<IObserver> observer) {
  observers.push_back(observer);
}

void Subject::removeObserver(std::shared_ptr<IObserver> observer) {
  // Find and remove the observer from the vector
  auto it = std::find(observers.begin(), observers.end(), observer);
  if (it != observers.end()) {
    observers.erase(it);
  }
}

void Subject::notify(GameEvent event) {
  // Notify all observers
  for (auto observer : observers) {
    observer->on_notify(event);
  }
}