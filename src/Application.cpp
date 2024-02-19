#include "Application.hpp"

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
#include <memory>

Application::Application() {
  m_ref.quit = FALSE;
}

void Application::run() {
  taskSetup();
  iconbarSetup();
  menuSetup();
  while(!m_ref.quit) {
    Event_Poll();
  }
}

void Application::taskSetup() {
  Resource_Initialise("!Gauntlet");
  Template_Initialise();
  Template_LoadFile("Templates");
  Event_Initialise("Gauntlet");
  Screen_CacheModeInfo();
}

void Application::iconbarSetup() {
  icon_handle barIcon;
  barIcon = Icon_BarIcon("!gauntlet", iconbar_RIGHT);
  Event_Claim(event_CLICK, -2, barIcon, click, (void*) &m_ref);
}

void Application::menuSetup() {
  // Menu options are delimited by |
  char menu[] = ">Info |Quit";
  dialog2_block* info;

  m_ref.menuhandle = Menu_New("Gauntlet", menu);

  info = Dialog2_CreateDialogBlock( "ProgInfo", -1, -1, NULL, NULL, NULL);
  Menu_Warn(m_ref.menuhandle, MenuOption::Info, TRUE, progInfo, (void*)info);
}

BOOL Application::click(event_pollblock* event, void* ref) {
  reference* ptr = static_cast<reference*>(ref);
  // Middle click brings up menu
  if(event->data.mouse.button.data.menu) {
    Menu_Show(ptr->menuhandle, event->data.mouse.pos.x, -1);
    Event_Claim(event_MENU, event_ANY, event_ANY, menuChoice, ref);
  }
  // Single click opens window
  else if(event->data.mouse.button.data.select) {
    windowOpen();
  }
    return TRUE;
}

BOOL Application::menuChoice(event_pollblock* event, void* ref) {
  reference* ptr = static_cast<reference*>(ref);
  // Maps the menu option selected to the handler
  switch(event->data.selection[0]) {
    case (MenuOption::Quit):
      Event_CloseDown();
      ptr->quit = TRUE;
      break;
  }
  return TRUE;  
}

BOOL Application::progInfo(event_pollblock* event, void* ref) {
  Dialog2_OpenDialogMenuLeaf(event, static_cast<dialog2_block*>(ref));
  return TRUE;
}

void Application::windowOpen() {

  // Start game to open SDL window
  std::unique_ptr<Game> game(new Game());
  game->run();
}
