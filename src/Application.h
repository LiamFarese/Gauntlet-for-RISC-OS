#pragma once

#include "DeskLib/Wimp.h"
#include "DeskLib/Core.h"

class Application {

public:
  Application();
  
  void run();

private:

  // Used for Event Handlers
  struct reference {
    BOOL          quit;
    menu_ptr      menuhandle;
    window_handle window;
  };

  reference ref;

  // A menu is stored as a char[], each option is indexed starting from 0
  enum MenuOption{
    Info = 0,
    Quit = 1
  };
  
  // Application setup functions 
  void taskSetup();
  void iconbarSetup();
  void menuSetup();
  void windowSetup();

  // Event handlers
  static auto click(event_pollblock* event, void* ref)       -> BOOL;
  static auto menuChoice(event_pollblock* event, void* ref)  -> BOOL;
  static auto progInfo(event_pollblock* event, void* ref)  -> BOOL;
  static void windowOpen(const char* windowName, void* ref);
  static auto windowClose(event_pollblock* event, void* ref) -> BOOL;
  static auto redraw(event_pollblock* event, void* ref)      -> BOOL;
};