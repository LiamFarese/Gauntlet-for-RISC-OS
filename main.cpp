#include <iostream>

#include "oslib/wimp.h"
#include "Event.h"

constexpr auto myfun(int x) -> int {
  return x * 2;
} 

auto main() -> int {
  std::cout << "Hello world \n";
  static constexpr int x {4};
  std::cout << myfun(x) << '\n';
  return 0;
}
