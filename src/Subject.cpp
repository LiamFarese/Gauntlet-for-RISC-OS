#include "Subject.hpp"

#include <algorithm>

Subject::Subject() {
}

void Subject::addObserver(std::shared_ptr<IObserver> observer) {
  observers_.push_back(observer);
}

void Subject::removeObserver(std::shared_ptr<IObserver> observer) {
  // Find and remove the observer from the vector
  auto it = std::find(observers_.begin(), observers_.end(), observer);
  if (it != observers_.end()) {
    observers_.erase(it);
  }
}

void Subject::notify(GameEvent event) {
  // Notify all observers_
  for (auto observer : observers_) {
    observer->on_notify(event);
  }
}