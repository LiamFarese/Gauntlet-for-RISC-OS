#include "DeskLib:Event.h"
#include "DeskLib:Core.h"

auto main() -> int {

  Event_InitNested("Test");

  while (TRUE) {
    Event_Poll();
  }
  return 0;
}
