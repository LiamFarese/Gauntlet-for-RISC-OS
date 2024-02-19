#pragma once

#include <DeskLib/Wimp.h>
#include <DeskLib/Core.h>

#include "Game.hpp"

class Application {

  // Used for Event Handlers
  struct reference {
    BOOL          quit;
    menu_ptr      menuhandle;
  };

  // A menu is stored as a char[], each option is indexed starting from 0
  enum MenuOption{
    Info = 0,
    Quit = 1
  };

public:

  Application();
  
  void run();

private:

  reference m_ref;
  
  // Application setup functions 
  void taskSetup();
  void iconbarSetup();
  void menuSetup();

  // Event handlers
  static BOOL click(event_pollblock* event, void* ref);
  static BOOL menuChoice(event_pollblock* event, void* ref);
  static BOOL progInfo(event_pollblock* event, void* ref);
  static void windowOpen();
};