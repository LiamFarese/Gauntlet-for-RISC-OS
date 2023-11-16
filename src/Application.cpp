#include "Application.h"

#include "DeskLib/Wimp.h"
#include "DeskLib/Event.h"
#include "DeskLib/Core.h"
#include "DeskLib/Resource.h"
#include "DeskLib/Icon.h"
#include "DeskLib/Menu.h"
#include "DeskLib/Screen.h"
#include "DeskLib/Template.h"
#include "DeskLib/Window.h"
#include "DeskLib/Handler.h"

namespace Application {

  // A menu is stored as a char[], each option is indexed starting from 0
  enum MenuOption{
    Info = 0,
    Quit = 1
  };

  void task_setup() {
    Resource_Initialise("!Gauntlet");
    Template_Initialise();
    Template_LoadFile("Templates");
    Event_Initialise("Gauntlet");
    Screen_CacheModeInfo();
  }

  void iconbar_setup(reference* ref) {
    icon_handle barIcon;
    barIcon = Icon_BarIcon("!icon", iconbar_RIGHT);
    Event_Claim(event_CLICK, -2, barIcon, click, (void*) ref);
  }

  void menu_setup(reference* ref) {
    // Menu options are delimited by |
    char menu[] = "Info |Quit";

    ref->menuhandle = Menu_New("Gauntlet", menu);
  }

  void window_setup() {
      Event_Claim(event_OPEN, event_ANY, event_ANY, Handler_OpenWindow, NULL);
  }

  void event_poll(reference* ref) {
    Event_Poll();
  }

  auto click(event_pollblock* event, void* ref) -> BOOL {
    reference* ptr = static_cast<reference*>(ref);
    // Middle click brings up menu
    if(event->data.mouse.button.data.menu) {
      Menu_Show(ptr->menuhandle, event->data.mouse.pos.x, -1);
      Event_Claim(event_MENU, event_ANY, event_ANY, menu_choice, ref);
    }
    // Single click opens window
    else if(event->data.mouse.button.data.select) {
      window_open("game", ref);
    }

    return(TRUE);
  }

  auto menu_choice(event_pollblock* event, void* ref) -> BOOL {
    reference* ptr = static_cast<reference*>(ref);

    // Maps the menu option selected to the handler
    switch(event->data.selection[0]) {
      case (MenuOption::Info):
        window_open("ProgInfo", ref);
        break;
      case (MenuOption::Quit):
        Event_CloseDown();
        ptr->quit = TRUE;
        break;
    }
    return(TRUE);  
  }

  void window_open(const char* windowName, void* ref) {
    reference* ptr = static_cast<reference*>(ref);

    // Window = 
    if(ptr->window == 0) ptr->window = Window_Create(windowName, 20);

    Window_Show(ptr->window, open_CENTERED);
    Event_Claim(event_CLOSE, ptr->window, event_ANY, window_close, ref);
  }

  auto window_close(event_pollblock* event, void* ref) -> BOOL {
    reference* ptr = static_cast<reference*>(ref);

    Window_Delete(ptr->window);
    ptr->window = 0;

    return(TRUE);
  }
}
