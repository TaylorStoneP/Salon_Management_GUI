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
#include "data_handler.h"
bool MyApp::OnInit()
{
    Main_Event_Window* frame = new Main_Event_Window(this);
    frame->Show(true);

    sm_NewBooking* newB = sm_NewBooking::get();
    //LOG_PRINT_LINE("Hello");
	
	data_handler::Add_Service(service("Cut", 30, 4.99));
	data_handler::Add_Service(service("Wash", 60, 9.99));
	data_handler::Add_Service(service("Dye", 90, 14.99));
	data_handler::Add_Service(service("Trim", 10, 10));
	data_handler::Add_Service(service("Perm", 40, 19.99));
	
    return true;
}
wxIMPLEMENT_APP(MyApp);

