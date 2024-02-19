#include "Application.hpp"

#include <memory>

#include <DeskLib/Wimp.h>
#include <DeskLib/WimpSWIs.h>
#include <DeskLib/Event.h>
#include <DeskLib/Core.h>
#include <DeskLib/Resource.h>
#include <DeskLib/Icon.h>
#include <DeskLib/Menu.h>
#include <DeskLib/Dialog2.h>
#include <DeskLib/Screen.h>
#include <DeskLib/Template.h>
#include <DeskLib/Handler.h>
#include <DeskLib/Coord.h>

Application::Application() {
  ref_.quit = FALSE;
}

void Application::run() {
  task_setup();
  iconbar_setup();
  menu_setup();
  while(!ref_.quit) {
    Event_Poll();
  }
}

void Application::task_setup() {
  Resource_Initialise("!Gauntlet");
  Template_Initialise();
  Template_LoadFile("Templates");
  Event_Initialise("Gauntlet");
  Screen_CacheModeInfo();
}

void Application::iconbar_setup() {
  icon_handle barIcon;
  barIcon = Icon_BarIcon("!gauntlet", iconbar_RIGHT);
  Event_Claim(event_CLICK, -2, barIcon, click, (void*) &ref_);
}

void Application::menu_setup() {
  // Menu options are delimited by |
  char menu[] = ">Info |Quit";
  dialog2_block* info;

  ref_.menu_handle = Menu_New("Gauntlet", menu);

  info = Dialog2_CreateDialogBlock( "ProgInfo", -1, -1, NULL, NULL, NULL);
  Menu_Warn(ref_.menu_handle, MenuOption::kInfo, TRUE, prog_info, (void*)info);
}

BOOL Application::click(event_pollblock* event, void* ref) {
  reference* ptr = static_cast<reference*>(ref);
  // Middle click brings up menu
  if(event->data.mouse.button.data.menu) {
    Menu_Show(ptr->menu_handle, event->data.mouse.pos.x, -1);
    Event_Claim(event_MENU, event_ANY, event_ANY, menu_choice, ref);
  }
  // Single click opens window
  else if(event->data.mouse.button.data.select) {
    window_open();
  }
    return TRUE;
}

BOOL Application::menu_choice(event_pollblock* event, void* ref) {
  reference* ptr = static_cast<reference*>(ref);
  // Maps the menu option selected to the handler
  switch(event->data.selection[0]) {
    case (MenuOption::kQuit):
      Event_CloseDown();
      ptr->quit = TRUE;
      break;
  }
  return TRUE;  
}

BOOL Application::prog_info(event_pollblock* event, void* ref) {
  Dialog2_OpenDialogMenuLeaf(event, static_cast<dialog2_block*>(ref));
  return TRUE;
}

void Application::window_open() {

  // Start game to open SDL window
  std::unique_ptr<Game> game(new Game());
  game->run();
}
