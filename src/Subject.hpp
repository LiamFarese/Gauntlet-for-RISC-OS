
#include <algorithm>
#include <vector>

#include "IObserver.hpp"

class Subject {
public:
    void addObserver(IObserver* observer) {
      observers.push_back(observer);
    }

    void removeObserver(IObserver* observer) {
      // Find and remove the observer from the vector
      auto it = std::find(observers.begin(), observers.end(), observer);
      if (it != observers.end()) {
        observers.erase(it);
      }
    }

    void notify(GameEvent event) {
      // Notify all observers
      for (IObserver* observer : observers) {
        observer->on_notify(event);
      }
    }

private:
  std::vector<IObserver*> observers;
};
