#pragma once

#include <DeskLib/Wimp.h>
#include <DeskLib/Core.h>

#include "Game.hpp"

class Application{

  // Used for Event Handlers
  struct reference {
    BOOL          quit;
    menu_ptr      menu_handle;
  };

  // A menu is stored as a char[], each option is indexed starting from 0
  enum MenuOption{
    kInfo = 0,
    kQuit = 1
  };

public:

  Application();
  
  void run();

private:

  reference ref_;
  
  // Application setup functions 
  void task_setup();
  void iconbar_setup();
  void menu_setup();

  // Event handlers
  static BOOL click(event_pollblock* event, void* ref);
  static BOOL menu_choice(event_pollblock* event, void* ref);
  static BOOL prog_info(event_pollblock* event, void* ref);
  static void window_open();
};