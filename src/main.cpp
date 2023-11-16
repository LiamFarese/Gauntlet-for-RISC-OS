#include "Application.h"

auto main() -> int {
  
  Application::reference ref;
  ref.quit = FALSE;
  ref.window = 0;

  Application::task_setup();
  Application::iconbar_setup(&ref);
  Application::menu_setup(&ref);
  Application::window_setup();

  while(!ref.quit) Application::event_poll(&ref);
  return 0;
}