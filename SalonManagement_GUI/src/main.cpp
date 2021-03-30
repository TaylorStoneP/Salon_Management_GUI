#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/graphics.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <CustomSetup.h>
#include "debuglogger.h"
#include "basePanel.h"
#include "wx/calctrl.h"
bool MyApp::OnInit()
{
    Main_Event_Window* frame = new Main_Event_Window(this);
    frame->Show(true);

    SubFrame* cal = new SubFrame(NULL,400,400,tp_colour_menus::menu_white);
    sm_BasePanel* main = new sm_BasePanel(cal,wxDefaultSize,tp_colour_menus::menu_black);
    wxCalendarCtrl* calendar = new wxCalendarCtrl(main,wxID_ANY);
    cal->Show(true);
    //LOG_PRINT_LINE("Hello");

    return true;
}
wxIMPLEMENT_APP(MyApp);

