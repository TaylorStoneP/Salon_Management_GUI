#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/graphics.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <CustomSetup.h>
#include "debuglogger.h"

bool MyApp::OnInit()
{
    Main_Event_Window* frame = new Main_Event_Window(this);
    frame->Show(true);

    //LOG_PRINT_LINE("Hello");

    return true;
}
wxIMPLEMENT_APP(MyApp);

