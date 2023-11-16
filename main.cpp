#include "Application.h"

auto main() -> int {
  
  Application::reference ref;
  ref.quit = FALSE;

  Application::task_setup();
  Application::iconbar_setup(&ref);
  Application::menu_setup(&ref);

  Application::event_loop(&ref);
  return 0;
}