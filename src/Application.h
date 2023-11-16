#ifndef GAUNTLET_APPLICATION_H
#define GAUNTLET_APPLICATION_H

#include "DeskLib/Wimp.h"
#include "DeskLib/Event.h"
#include "DeskLib/Core.h"
#include "DeskLib/Resource.h"
#include "DeskLib/Icon.h"
#include "DeskLib/Menu.h"
#include "DeskLib/Screen.h"
#include "DeskLib/Template.h"

namespace Application {

  // Used for Event Handlers
  struct reference {
      BOOL     quit;
      menu_ptr menuhandle;
    };

  // Application setup functions 
  void task_setup();
  void iconbar_setup(reference* ref);
  void menu_setup(reference* ref);

  // Event handlers
  auto click(event_pollblock* event, void* ref) -> BOOL;
  auto menu_choice(event_pollblock *event, void *ref) -> BOOL;

  // Encapsulate Event_Poll function
  void event_poll(reference* ref);
}

#endif