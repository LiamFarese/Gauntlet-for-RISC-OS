#include "Application.h"

#include "DeskLib/Wimp.h"
#include "DeskLib/WimpSWIs.h"
#include "DeskLib/Event.h"
#include "DeskLib/Core.h"
#include "DeskLib/Resource.h"
#include "DeskLib/Icon.h"
#include "DeskLib/Menu.h"
#include "DeskLib/Dialog2.h"
#include "DeskLib/Screen.h"
#include "DeskLib/Template.h"
#include "DeskLib/Window.h"
#include "DeskLib/Handler.h"
#include "DeskLib/Sprite.h"
#include "DeskLib/Coord.h"

Application::Application() {
  ref.quit = FALSE;
  ref.window = 0;
}

void Application::run() {
  taskSetup();
  iconbarSetup();
  menuSetup();
  windowSetup();
  while(!ref.quit) Event_Poll();
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
  Event_Claim(event_CLICK, -2, barIcon, click, (void*) &ref);
}

void Application::menuSetup() {
  // Menu options are delimited by |
  char menu[] = ">Info |Quit";
  dialog2_block* info;

  ref.menuhandle = Menu_New("Gauntlet", menu);

  info = Dialog2_CreateDialogBlock( "ProgInfo", -1, -1, NULL, NULL, NULL);
  Menu_Warn(ref.menuhandle, MenuOption::Info, TRUE, progInfo, (void*)info);
}

void Application::windowSetup() {
  static char sblck[1500000];
  static sprite_areainfo* sblock = (sprite_areainfo*)sblck;

  Sprite_Load((sprite_area)sblock, "<!Gauntlet$Dir>.sprites");

  Event_Claim(event_OPEN, event_ANY, event_ANY, Handler_OpenWindow, NULL);
  Event_Claim(event_REDRAW, event_ANY, event_ANY, redraw,  (void*)sblock);
}

auto Application::click(event_pollblock* event, void* ref) -> BOOL {
  reference* ptr = static_cast<reference*>(ref);
  // Middle click brings up menu
  if(event->data.mouse.button.data.menu) {
    Menu_Show(ptr->menuhandle, event->data.mouse.pos.x, -1);
    Event_Claim(event_MENU, event_ANY, event_ANY, menuChoice, ref);
  }
  // Single click opens window
  else if(event->data.mouse.button.data.select) {
    windowOpen("game", ref);
  }
    return TRUE;
}

auto Application::menuChoice(event_pollblock* event, void* ref) -> BOOL {
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

auto Application::progInfo(event_pollblock* event, void* ref) -> BOOL {
  Dialog2_OpenDialogMenuLeaf(event, static_cast<dialog2_block*>(ref));
  return TRUE;
}

void Application::windowOpen(const char* windowName, void* ref) {
  reference* ptr = static_cast<reference*>(ref);
  // Window = 0 means there is no active window
  if(ptr->window == 0) ptr->window = Window_Create(windowName, 20);
    
  Window_Show(ptr->window, open_CENTERED);
  Event_Claim(event_CLOSE, ptr->window, event_ANY, windowClose, ref);
}

auto Application::windowClose(event_pollblock* event, void* ref) -> BOOL {
  reference* ptr = static_cast<reference*>(ref);

  Window_Delete(ptr->window);
  ptr->window = 0;

  return TRUE;
}

auto Application::redraw(event_pollblock* event, void* ref) -> BOOL {
  window_redrawblock redraw;
  BOOL more;
  wimp_point point;
  convert_block convert;

  sprite_areainfo* sblock = static_cast<sprite_areainfo*>(ref);

  point.x=0;
  point.y=-800;

  redraw.window = event->data.openblock.window;
  Window_GetCoords(redraw.window, &convert);
  Wimp_RedrawWindow(&redraw, &more);

  while (more)
  {
    Sprite_WimpPlot((sprite_area)sblock, "entities", &point, &convert, 0);
    Wimp_GetRectangle(&redraw, &more);
  }

  return TRUE;
}
