#include "Application.h"

namespace Application {

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

    char menu[] = "Quit";
    ref->menuhandle = Menu_New("Gauntlet", menu);
  }

  void event_poll(reference* ref) {
    Event_Poll();
  }

  auto click(event_pollblock *event, void* ref) -> BOOL {

    struct reference* ptr;

    ptr = (struct reference *) ref;

    if(event->data.mouse.button.data.menu) {

      Menu_Show(ptr->menuhandle, event->data.mouse.pos.x, -1);
      Event_Claim(event_MENU, event_ANY, event_ANY, menu_choice, ref);
    }
    else if(event->data.mouse.button.data.select) {

      Event_CloseDown();
      ptr->quit = TRUE;
    }

    return(TRUE);
  }

  auto menu_choice(event_pollblock* event, void* ref) -> BOOL
  {
    struct reference* ptr;

    ptr = (struct reference *)ref;

  /* Check which menu point was selected ***************************************/
    if(event->data.selection[0] == 0){
  /* If 'Quit' was selected, close the task down and end polling loop. *********/
      Event_CloseDown();
      ptr->quit = TRUE;
    }
    return(TRUE);  
  }

}
