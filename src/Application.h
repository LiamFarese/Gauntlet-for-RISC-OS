#pragma once

#include "DeskLib/Wimp.h"
#include "DeskLib/Core.h"

namespace Application {

  // Used for Event Handlers
  struct reference {
      BOOL          quit;
      menu_ptr      menuhandle;
      window_handle window;
    };

  // Application setup functions 
  void task_setup();
  void iconbar_setup(reference* ref);
  void menu_setup(reference* ref);
  void window_setup();

  // Event handlers
  auto click(event_pollblock* event, void* ref)        -> BOOL;
  auto menu_choice(event_pollblock* event, void* ref)  -> BOOL;
  void window_open(const char* windowName, void* ref);
  auto window_close(event_pollblock* event, void* ref) -> BOOL;

  // Encapsulate Event_Poll function
  void event_poll(reference* ref);
}