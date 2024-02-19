#include "Application.hpp"
#include <memory>

int main(int argc, char* args[]) {
  std::unique_ptr<Application> application(new Application());
  application->run();
  return 0;
}