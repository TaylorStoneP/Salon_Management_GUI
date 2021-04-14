#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/menu.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <wx/calctrl.h>
#include "random.h"
#include <basePanel.h>
#include "data_handler.h"
sm_BasePanel::sm_BasePanel(wxWindow* window, wxSize size, wxColour colour, int style) : wxWindow(window,wxID_ANY,wxDefaultPosition,size,style)
{
	this->SetBackgroundColour(colour);
	if (size != wxDefaultSize) {
		this->SetMaxSize(size);
		this->SetMinSize(size);
	}
}

sm_Booking::sm_Booking(wxWindow* window, wxSize size, wxColour colour, int style) : sm_BasePanel(window,size,colour,style)
{
	//this->Show(false);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxArrayString choices;
	choices.Add("Wash");
	choices.Add("Cut");
	choices.Add("Dye");

	name = new wxTextCtrl(this,wxID_ANY,"Name");
	phone = new wxTextCtrl(this,wxID_ANY,"Phone");
	service = new wxComboBox(this,wxID_ANY,"-Choose Service-",wxDefaultPosition,wxDefaultSize,choices);
	done = new wxButton(this, wxID_ANY, "Submit");
	done->SetMaxSize({ 80,-1 });
	sizer->Add(name, 1, wxALL | wxEXPAND);
	sizer->Add(phone, 1, wxALL | wxEXPAND);
	sizer->Add(service, 1, wxALL | wxEXPAND);
	sizer->Add(done, 1, wxALL | wxEXPAND);
	SetSizer(sizer,false);

}


void ScrolledWidgetsPane::update()
{
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
	this->Layout();
}

ScrolledWidgetsPane::ScrolledWidgetsPane(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
{
    // the sizer will take care of determining the needed scroll size
    // (if you don't use sizers you will need to manually set the viewport size)
    sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizer);
    update();
}
void ScrolledWidgetsPane::add_widget(wxWindow* widget)
{
    sizer->Add(widget, 1, wxALL | wxEXPAND);
    update();
}
void ScrolledWidgetsPane::remove_widget(int index)
{
    if (m_children.GetCount() != 0) {
        m_children[index]->Destroy();
        update();
    }
}
void sm_row_array_pane::update()
{
	this->FitInside(); // ask the sizer about the needed size
}
sm_row_array_pane::sm_row_array_pane(wxWindow* parent) : sm_BasePanel(parent,wxDefaultSize,tp_colour_misc::deep_blue)
{
	sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizer);
}
void sm_row_array_pane::add_widget(wxWindow* widget)
{
	sizer->Add(widget, 1, wxALL | wxEXPAND);
	this->Layout();
}
void sm_row_array_pane::remove_widget(int index)
{
	if (m_children.GetCount() != 0) {
		m_children[index]->Destroy();
	}
	this->Layout();
}

sm_StaffBookingPanel::sm_StaffBookingPanel(wxWindow* parent, int staff_index):sm_BasePanel(parent,wxSize(-1,50)),staff(nullptr)
{
	staff = &data_handler::Get_Staff()[staff_index];
	this->Hide();
	wxBoxSizer* hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hori_sizer);
	//int total_width = 0;
	int unit_width = 80;
	int unit_height = 50;

	sm_BasePanel* staff_box = new sm_BasePanel(this, wxSize(unit_width * 1.5f, unit_height), tp_colour_menus::menu_grey, wxSUNKEN_BORDER);
	hori_sizer->Add(staff_box, 1, wxALL | wxEXPAND);
	wxBoxSizer* box_filler = new wxBoxSizer(wxHORIZONTAL);
	staff_box->SetSizer(box_filler);
	wxTextCtrl* staff_text = new wxTextCtrl(staff_box,wxID_ANY,staff->m_name,wxDefaultPosition,wxDefaultSize, wxTE_CENTRE| wxTE_READONLY| wxTE_MULTILINE| wxTE_NO_VSCROLL);
	box_filler->Add(staff_text,1, wxALL | wxEXPAND);
	//total_width += unit_width * 1.5f;
	
	sm_BasePanel* hours_box = new sm_BasePanel(this, wxSize(this->GetClientSize().GetX()-staff_box->GetClientSize().GetWidth(),unit_height),tp_colour_menus::menu_grey, wxSUNKEN_BORDER);
	hori_sizer->Add(hours_box, 1, wxALL | wxEXPAND);

	wxBoxSizer* hours_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	hours_box->SetSizer(hours_box_sizer);

	wxSize unit_size(hours_box->GetMaxSize().x/14, unit_height);
	wxSize sub_unit_size(-1, unit_height/2);
	for (int i = 7; i < 22; i++)
	{
		sm_BasePanel* unit = new sm_BasePanel(hours_box, unit_size,tp_colour_menus::menu_grey);
		wxBoxSizer* indiv_dual = new wxBoxSizer(wxVERTICAL);

		sm_BasePanel* hour = new sm_BasePanel(unit, sub_unit_size,tp_colour_menus::menu_black);
		wxTextCtrl* hour_text = new wxTextCtrl(hour,wxID_ANY,std::to_string(i), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE | wxTE_READONLY | wxTE_MULTILINE | wxTE_NO_VSCROLL);
		wxBoxSizer* box_filler_hour = new wxBoxSizer(wxHORIZONTAL);
		box_filler_hour->Add(hour_text, 1, wxALL | wxEXPAND);
		hour->SetSizer(box_filler_hour);

		sm_Slot_Button* slot = new sm_Slot_Button(unit,wxSize(-1,-1),"",i,staff);
		slot->SetBackgroundColour(tp_colour_log::light);
		indiv_dual->Add(hour, 1, wxALL | wxEXPAND);
		indiv_dual->Add(slot, 1, wxALL | wxEXPAND);
		unit->SetSizer(indiv_dual);
		hours_box_sizer->Add(unit, 1, wxALL | wxEXPAND);
		//total_width += unit_width;
	}

	this->Show();
}

sm_DateTimeBox::sm_DateTimeBox() : SubFrame(Main_Event_Window::get(), 300, 300, tp_colour_menus::menu_black), date(nullptr)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	calendar = new wxCalendarCtrl(this, wxID_ANY);
	wxArrayString myChoicesHour;
	for (int i = 0; i < 24; i++)
	{
		myChoicesHour.Add(std::to_string(i)); // populate the array
	}
	wxArrayString myChoicesMinSec;
	for (int i = 0; i < 60; i++)
	{
		myChoicesMinSec.Add(std::to_string(i)); // populate the array
	}
	sm_BasePanel* hour_slot_panel = new sm_BasePanel(this,wxSize(-1,30),tp_colour_menus::menu_black);
	wxBoxSizer* hour_sizer = new wxBoxSizer(wxHORIZONTAL);
	hour_slot_panel->SetSizer(hour_sizer);
	sm_BasePanel* hour_slot = new sm_BasePanel(hour_slot_panel,wxSize(-1,-1));
	wxBoxSizer* hour_slot_sizer = new wxBoxSizer(wxHORIZONTAL);
	hour_slot->SetSizer(hour_slot_sizer);
	hour = new wxChoice(hour_slot, wxID_ANY,wxDefaultPosition, wxDefaultSize, myChoicesHour, 0);
	hour->SetSelection(0);
	minute = new wxChoice(hour_slot, wxID_ANY,wxDefaultPosition, wxDefaultSize, myChoicesMinSec, 0);
	minute->SetSelection(0);
	hour_slot_sizer->Add(hour, 1, wxALL | wxEXPAND);
	hour_slot_sizer->Add(minute, 1, wxALL | wxEXPAND);
	hour_sizer->Add(hour_slot, 1, wxALL | wxEXPAND);
	finish = new sm_Button(this, &sm_DateTimeBox::SetDate, this, wxSize(-1, 40), "Done");
	sizer->Add(calendar, 1, wxALL | wxEXPAND);
	sizer->Add(hour_slot_panel, 1, wxALL | wxEXPAND);
	sizer->Add(finish, 1, wxALL | wxEXPAND);
	SetSizer(sizer);
	this->Show(true);
}
void sm_DateTimeBox::Extra(){ LOG_TRACE("Extra() not overridden"); }
void sm_DateTimeBox::SetDate(wxCommandEvent& event)
{
	int year = calendar->GetDate().GetYear();
	int month = calendar->GetDate().GetMonth()+1;
	int day = calendar->GetDate().GetDay();
	*date = DateTime(year, month, day, hour->GetSelection(), minute->GetSelection());
	Extra();
	this->Close();
}

sm_DateBox::sm_DateBox() : SubFrame(Main_Event_Window::get(), 300, 300, tp_colour_menus::menu_black), date(nullptr)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	calendar = new wxCalendarCtrl(this, wxID_ANY);	wxBoxSizer* hour_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(this, &sm_DateBox::SetDate, this, wxSize(-1, 40), "Done");
	sizer->Add(calendar, 1, wxALL | wxEXPAND);
	sizer->Add(finish, 1, wxALL | wxEXPAND);
	SetSizer(sizer);
	this->Show(true);
}
void sm_DateBox::Extra() {
	LOG_TRACE("Extra() not overridden");
	for (int i = 0; i < data_handler::Get_Staff().count(); i++) {
		UpdateStaffTimeslotsAt(i);
	}
}
void sm_DateBox::SetDate(wxCommandEvent& event)
{
	int year = calendar->GetDate().GetYear();
	int month = calendar->GetDate().GetMonth() + 1;
	int day = calendar->GetDate().GetDay();
	*date = DateTime(year, month, day, 0, 0);
	Extra();
	this->Close();
}

sm_ShiftBox::sm_ShiftBox(bool alternate) : SubFrame(Main_Event_Window::get(), 300, 300, tp_colour_menus::menu_black), shift(nullptr), alternate(alternate)
{
	sm_BasePanel* weekday_box = nullptr;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	if (alternate)
	{
		wxArrayString myChoicesDay;
		myChoicesDay.Add("-Week Day");
		myChoicesDay.Add("Monday");
		myChoicesDay.Add("Tuesday");
		myChoicesDay.Add("Wednesday");
		myChoicesDay.Add("Thursday");
		myChoicesDay.Add("Friday");
		myChoicesDay.Add("Saturday");
		myChoicesDay.Add("Sunday");
		calendar = nullptr;
		weekday_box = new sm_BasePanel(this, wxSize(-1, 30), tp_colour_menus::menu_black);
		wxBoxSizer* weekday_box_sizer = new wxBoxSizer(wxHORIZONTAL);
		weekday_box->SetSizer(weekday_box_sizer);
		weekday = new wxChoice(weekday_box, wxID_ANY, wxDefaultPosition, wxDefaultSize, myChoicesDay, 0);
		weekday_box_sizer->Add(weekday, 1, wxALL | wxEXPAND);
		weekday->SetSelection(0);
	}
	else
	{
		calendar = new wxCalendarCtrl(this, wxID_ANY);
		weekday = nullptr;
	}
	wxArrayString myChoicesHour;
	for (int i = 0; i < 24; i++)
	{
		myChoicesHour.Add(std::to_string(i)); // populate the array
	}
	wxArrayString myChoicesMinSec;
	for (int i = 0; i < 60; i++)
	{
		myChoicesMinSec.Add(std::to_string(i)); // populate the array
	}
	sm_BasePanel* start_hour_slot_panel = new sm_BasePanel(this,wxSize(-1,30),tp_colour_menus::menu_black);
	wxBoxSizer* start_hour_sizer = new wxBoxSizer(wxHORIZONTAL);
	start_hour_slot_panel->SetSizer(start_hour_sizer);
	sm_BasePanel* start_hour_slot = new sm_BasePanel(start_hour_slot_panel,wxSize(-1,-1));
	wxBoxSizer* start_hour_slot_sizer = new wxBoxSizer(wxHORIZONTAL);
	start_hour_slot->SetSizer(start_hour_slot_sizer);
	start_hour = new wxChoice(start_hour_slot, wxID_ANY,wxDefaultPosition, wxDefaultSize, myChoicesHour, 0);
	start_hour->SetSelection(0);
	start_minute = new wxChoice(start_hour_slot, wxID_ANY,wxDefaultPosition, wxDefaultSize, myChoicesMinSec, 0);
	start_minute->SetSelection(0);
	start_hour_slot_sizer->Add(start_hour, 1, wxALL | wxEXPAND);
	start_hour_slot_sizer->Add(start_minute, 1, wxALL | wxEXPAND);
	start_hour_sizer->Add(start_hour_slot, 1, wxALL | wxEXPAND);

	sm_BasePanel* finish_hour_slot_panel = new sm_BasePanel(this, wxSize(-1, 30), tp_colour_menus::menu_black);
	wxBoxSizer* finish_hour_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish_hour_slot_panel->SetSizer(finish_hour_sizer);
	sm_BasePanel* finish_hour_slot = new sm_BasePanel(finish_hour_slot_panel, wxSize(-1, -1));
	wxBoxSizer* finish_hour_slot_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish_hour_slot->SetSizer(finish_hour_slot_sizer);
	finish_hour = new wxChoice(finish_hour_slot, wxID_ANY, wxDefaultPosition, wxDefaultSize, myChoicesHour, 0);
	finish_hour->SetSelection(0);
	finish_minute = new wxChoice(finish_hour_slot, wxID_ANY, wxDefaultPosition, wxDefaultSize, myChoicesMinSec, 0);
	finish_minute->SetSelection(0);
	finish_hour_slot_sizer->Add(finish_hour, 1, wxALL | wxEXPAND);
	finish_hour_slot_sizer->Add(finish_minute, 1, wxALL | wxEXPAND);
	finish_hour_sizer->Add(finish_hour_slot, 1, wxALL | wxEXPAND);


	finish = new sm_Button(this, &sm_ShiftBox::SetShift, this, wxSize(-1, 40), "Done");
	if (alternate)
	{
		sizer->Add(weekday_box, 1, wxALL | wxEXPAND);
	}
	else
	{
		sizer->Add(calendar, 1, wxALL | wxEXPAND);
	}
	sizer->Add(start_hour_slot_panel, 1, wxALL | wxEXPAND);
	sizer->Add(finish_hour_slot_panel, 1, wxALL | wxEXPAND);
	sizer->Add(finish, 1, wxALL | wxEXPAND);
	SetSizer(sizer);
	this->Show(true);
}
void sm_ShiftBox::Extra(){ LOG_TRACE("Extra() not overridden"); }
void sm_ShiftBox::SetShift(wxCommandEvent& event)
{
	if(alternate)
	{
		DateTime start(start_hour->GetSelection(), start_minute->GetSelection());
		DateTime finish(finish_hour->GetSelection(), finish_minute->GetSelection());
		*shift = working_period((week_day)(weekday->GetSelection()-1), start, finish);
	}
	else
	{
		int year = calendar->GetDate().GetYear();
		int month = calendar->GetDate().GetMonth() + 1;
		int day = calendar->GetDate().GetDay();
		DateTime start(year, month, day, start_hour->GetSelection(), start_minute->GetSelection());
		DateTime finish(year, month, day, finish_hour->GetSelection(), finish_minute->GetSelection());
		*shift = working_period((week_day)(start.to_tm()->tm_wday == 0 ? 6 : start.to_tm()->tm_wday - 1), start, finish);
	}
	Extra();
	this->Close();
}

void sm_NewBooking::add_service_to_list(wxCommandEvent& event)
{
	services->AppendText(service->GetStringSelection()+"\n");
	services_list.add_back(data_handler::Get_Service_By_Name((std::string)service->GetStringSelection()));
}
void sm_NewBooking::get_date_picker(wxCommandEvent& event)
{
	sm_NewBooking_DateTimeBox::sm_GetDateTime<sm_NewBooking_DateTimeBox>(&datetime_val);
}
void sm_NewBooking::add_booking_to_staff(wxCommandEvent& event)
{
	for (int i = 0;i<data_handler::Get_Staff().count(); i++)
	{
		if ((std::string)staff->GetStringSelection() == data_handler::Get_Staff()[i].m_name)
		{
			Booking booking_temp(	(std::string)name->WXGetTextEntry()->GetValue(),
									(std::string)phone->WXGetTextEntry()->GetValue(),
									nullptr,
									services_list,
									datetime_val,
									false,
									false);
			data_handler::Get_Staff()[i].addBooking(booking_temp);
			LOG_TRACE("New Booking Added: "+data_handler::Get_Staff()[i].getBookings().to_string());
		}
	}
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		UpdateStaffTimeslotsAt(i);
	}
	Close();
}
sm_NewBooking* sm_NewBooking::instance = nullptr;
bool sm_NewBooking::created = false;
sm_NewBooking* sm_NewBooking::get()
{
	if (created == false)
	{
		instance = new sm_NewBooking();
	}
	return instance;
}

sm_NewBooking::sm_NewBooking(): SubFrame(Main_Event_Window::get(), 500, 250, tp_colour_menus::menu_black)
{
	created = true;
	instance = this;
	name		= nullptr;
	phone		= nullptr;
	staff		= nullptr;
	service		= nullptr;
	services	= nullptr;
	add_service	= nullptr;
	datetime	= nullptr;
	get_date	= nullptr;
	finish		= nullptr;
	wxBoxSizer* verti_sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(verti_sizer);
	sm_BasePanel* panel_main_top = new sm_BasePanel(this,wxSize(-1,50),tp_colour_misc::cyan);
	sm_BasePanel* panel_main_bottom = new sm_BasePanel(this,wxSize(-1,-1),tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this,wxSize(-1,-1),tp_colour_misc::deep_blue);
	verti_sizer->Add(panel_main_top, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_bottom, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_fin, 1, wxALL | wxEXPAND);

	//TOP PANEL WORKINGS
	wxBoxSizer* panel_main_top_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_top->SetSizer(panel_main_top_hori_sizer);
	sm_BasePanel* panel_main_top_name_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_top_phone_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_top_staff_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::orange);
	panel_main_top_hori_sizer->Add(panel_main_top_name_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_phone_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_staff_box, 1, wxALL | wxEXPAND);
	
	//NAME
	wxBoxSizer* panel_main_top_name_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	name = new wxTextCtrl(panel_main_top_name_box,wxID_ANY,"-Name");
	panel_main_top_name_box->SetSizer(panel_main_top_name_box_sizer);
	panel_main_top_name_box_sizer->Add(name, 1, wxALL | wxEXPAND);
	////////////////////

	//PHONE
	wxBoxSizer* panel_main_top_phone_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	phone = new wxTextCtrl(panel_main_top_phone_box, wxID_ANY, "-Phone");
	panel_main_top_phone_box->SetSizer(panel_main_top_phone_box_sizer);
	panel_main_top_phone_box_sizer->Add(phone, 1, wxALL | wxEXPAND);
	////////////////////

	//STAFF
	wxArrayString staffNames;

	staffNames.Add("-Staff"); // populate the array
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		staffNames.Add(data_handler::Get_Staff()[i].m_name); // populate the array
	}
	
	wxBoxSizer* panel_main_top_staff_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	staff = new wxChoice(panel_main_top_staff_box, wxID_ANY, wxDefaultPosition, wxDefaultSize, staffNames, 0);
	staff->SetSelection(0);
	panel_main_top_staff_box->SetSizer(panel_main_top_staff_box_sizer);
	panel_main_top_staff_box_sizer->Add(staff, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM PANEL WORKINGS
	wxBoxSizer* panel_main_bottom_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_bottom->SetSizer(panel_main_bottom_hori_sizer);
	sm_BasePanel* panel_main_bottom_service_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_services_list_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::red);
	sm_BasePanel* panel_main_bottom_date_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::yellow);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_service_box, 1, wxALL | wxEXPAND);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_services_list_box, 1, wxALL | wxEXPAND);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_date_box, 1, wxALL | wxEXPAND);

	//ALLSERVICES
	wxBoxSizer* panel_main_bottom_service_box_sizer = new wxBoxSizer(wxVERTICAL);
	panel_main_bottom_service_box->SetSizer(panel_main_bottom_service_box_sizer);
	sm_BasePanel* panel_main_bottom_service_box_top = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_service_box_bottom = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_top, 1, wxALL | wxEXPAND);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_bottom, 1, wxALL | wxEXPAND);
	//SERVICE
	wxArrayString serviceNames;

	serviceNames.Add("-Service"); // populate the array
	for (int i = 0; i < data_handler::Get_Services().count();i++)
	{
		serviceNames.Add(data_handler::Get_Services()[i].m_name);
	}

	wxBoxSizer* panel_main_bottom_service_box_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	service = new wxChoice(panel_main_bottom_service_box_top, wxID_ANY, wxDefaultPosition, wxDefaultSize, serviceNames, 0);
	service->SetSelection(0);
	panel_main_bottom_service_box_top->SetSizer(panel_main_bottom_service_box_top_sizer);
	panel_main_bottom_service_box_top_sizer->Add(service, 1, wxALL | wxEXPAND);
	////////////////////

	//ADDSERVICE
	wxBoxSizer* panel_main_top_service_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	add_service = new sm_Button(panel_main_bottom_service_box_bottom,&sm_NewBooking::add_service_to_list,this,wxDefaultSize,"Add>>");
	panel_main_bottom_service_box_bottom->SetSizer(panel_main_top_service_box_bottom_sizer);
	panel_main_top_service_box_bottom_sizer->Add(add_service, 1, wxALL | wxEXPAND);
	////////////////////
	//SERVICESLISTBOX
	wxBoxSizer* panel_main_bottom_services_list_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	services = new wxTextCtrl(panel_main_bottom_services_list_box, wxID_ANY, "", wxDefaultPosition,wxDefaultSize, wxTE_READONLY| wxTE_MULTILINE);
	panel_main_bottom_services_list_box->SetSizer(panel_main_bottom_services_list_box_sizer);
	panel_main_bottom_services_list_box_sizer->Add(services, 1, wxALL | wxEXPAND);
	////////////////////

	//DATESTART
	wxBoxSizer* panel_main_bottom_date_box_sizer = new wxBoxSizer(wxVERTICAL);
	panel_main_bottom_date_box->SetSizer(panel_main_bottom_date_box_sizer);
	sm_BasePanel* panel_main_bottom_date_box_top = new sm_BasePanel(panel_main_bottom_date_box, wxSize(-1, 50), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_date_box_bottom = new sm_BasePanel(panel_main_bottom_date_box, wxSize(-1, 50), tp_colour_misc::purple);
	panel_main_bottom_date_box_sizer->Add(panel_main_bottom_date_box_top, 1, wxALL | wxEXPAND);
	panel_main_bottom_date_box_sizer->Add(panel_main_bottom_date_box_bottom, 1, wxALL | wxEXPAND);
	////////////////////
	//DATESTRING
	wxBoxSizer* panel_main_bottom_date_box_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	datetime = new wxTextCtrl(panel_main_bottom_date_box_top, wxID_ANY, "-Date & Time", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	panel_main_bottom_date_box_top->SetSizer(panel_main_bottom_date_box_top_sizer);
	panel_main_bottom_date_box_top_sizer->Add(datetime, 1, wxALL | wxEXPAND);
	////////////////////
	//DATEPICK
	wxBoxSizer* panel_main_bottom_date_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	get_date = new sm_Button(panel_main_bottom_date_box_bottom, &sm_NewBooking::get_date_picker, this, wxDefaultSize, "Get Timeslot");
	panel_main_bottom_date_box_bottom->SetSizer(panel_main_bottom_date_box_bottom_sizer);
	panel_main_bottom_date_box_bottom_sizer->Add(get_date, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_NewBooking::add_booking_to_staff, this, wxDefaultSize, "Add Booking");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////

	this->Show(true);
}

sm_NewBooking::~sm_NewBooking()
{
	created = false;
}


void sm_UpdateBooking::add_service_to_list(wxCommandEvent& event)
{
	services->AppendText(service->GetStringSelection() + "\n");
	services_list.add_back(data_handler::Get_Service_By_Name((std::string)service->GetStringSelection()));
}
void sm_UpdateBooking::get_date_picker(wxCommandEvent& event)
{
	sm_UpdateBooking_DateTimeBox::sm_GetDateTime<sm_UpdateBooking_DateTimeBox>(&datetime_val);
}
void sm_UpdateBooking::update_booking(wxCommandEvent& event)
{
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		if ((std::string)staff->GetStringSelection() == data_handler::Get_Staff()[i].m_name)
		{
			Booking booking_temp((std::string)name->WXGetTextEntry()->GetValue(),
				(std::string)phone->WXGetTextEntry()->GetValue(),
				&data_handler::Get_Staff()[i],
				services_list,
				datetime_val,
				false,
				paid->GetValue());
			*booking = booking_temp;
			LOG_TRACE("Booking Updated: " + data_handler::Get_Staff()[i].getBookings().to_string());
		}
	}
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		UpdateStaffTimeslotsAt(i);
	}
	Close();
}
sm_UpdateBooking* sm_UpdateBooking::instance = nullptr;
bool sm_UpdateBooking::created = false;
sm_UpdateBooking* sm_UpdateBooking::get()
{
	return instance;
}

sm_UpdateBooking::sm_UpdateBooking(Booking* cur_booking) : SubFrame(Main_Event_Window::get(), 500, 250, tp_colour_menus::menu_black)
{
	booking = cur_booking;
	datetime_val = booking->getMtimeSlot();
	created = true;
	instance = this;
	name = nullptr;
	phone = nullptr;
	staff = nullptr;
	service = nullptr;
	services = nullptr;
	add_service = nullptr;
	datetime = nullptr;
	get_date = nullptr;
	finish = nullptr;
	wxBoxSizer* verti_sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(verti_sizer);
	sm_BasePanel* panel_main_top = new sm_BasePanel(this, wxSize(-1, 50), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_bottom = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_paid = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_menus::menu_white);
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::deep_blue);
	verti_sizer->Add(panel_main_top, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_bottom, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_paid, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_fin, 1, wxALL | wxEXPAND);

	//TOP PANEL WORKINGS
	wxBoxSizer* panel_main_top_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_top->SetSizer(panel_main_top_hori_sizer);
	sm_BasePanel* panel_main_top_name_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_top_phone_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_top_staff_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::orange);
	panel_main_top_hori_sizer->Add(panel_main_top_name_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_phone_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_staff_box, 1, wxALL | wxEXPAND);

	//NAME
	wxBoxSizer* panel_main_top_name_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	name = new wxTextCtrl(panel_main_top_name_box, wxID_ANY, booking->getMname());
	panel_main_top_name_box->SetSizer(panel_main_top_name_box_sizer);
	panel_main_top_name_box_sizer->Add(name, 1, wxALL | wxEXPAND);
	////////////////////

	//PHONE
	wxBoxSizer* panel_main_top_phone_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	phone = new wxTextCtrl(panel_main_top_phone_box, wxID_ANY, booking->getMphone());
	panel_main_top_phone_box->SetSizer(panel_main_top_phone_box_sizer);
	panel_main_top_phone_box_sizer->Add(phone, 1, wxALL | wxEXPAND);
	////////////////////

	//STAFF
	wxArrayString staffNames;

	staffNames.Add("-Staff"); // populate the array
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		staffNames.Add(data_handler::Get_Staff()[i].m_name); // populate the array
	}

	wxBoxSizer* panel_main_top_staff_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	staff = new wxChoice(panel_main_top_staff_box, wxID_ANY, wxDefaultPosition, wxDefaultSize, staffNames, 0);
	int index=0;
	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		if (data_handler::Get_Staff()[i].m_name == booking->getMstaff()->m_name)
		{
			index = i;
		}
	}
	staff->SetSelection(1+index);
	panel_main_top_staff_box->SetSizer(panel_main_top_staff_box_sizer);
	panel_main_top_staff_box_sizer->Add(staff, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM PANEL WORKINGS
	wxBoxSizer* panel_main_bottom_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_bottom->SetSizer(panel_main_bottom_hori_sizer);
	sm_BasePanel* panel_main_bottom_service_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_services_list_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::red);
	sm_BasePanel* panel_main_bottom_date_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::yellow);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_service_box, 1, wxALL | wxEXPAND);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_services_list_box, 1, wxALL | wxEXPAND);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_date_box, 1, wxALL | wxEXPAND);

	//ALLSERVICES
	wxBoxSizer* panel_main_bottom_service_box_sizer = new wxBoxSizer(wxVERTICAL);
	panel_main_bottom_service_box->SetSizer(panel_main_bottom_service_box_sizer);
	sm_BasePanel* panel_main_bottom_service_box_top = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_service_box_bottom = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_top, 1, wxALL | wxEXPAND);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_bottom, 1, wxALL | wxEXPAND);
	//SERVICE
	wxArrayString serviceNames;

	serviceNames.Add("-Service"); // populate the array
	for (int i = 0; i < data_handler::Get_Services().count(); i++)
	{
		serviceNames.Add(data_handler::Get_Services()[i].m_name);
	}

	wxBoxSizer* panel_main_bottom_service_box_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	service = new wxChoice(panel_main_bottom_service_box_top, wxID_ANY, wxDefaultPosition, wxDefaultSize, serviceNames, 0);
	service->SetSelection(0);
	panel_main_bottom_service_box_top->SetSizer(panel_main_bottom_service_box_top_sizer);
	panel_main_bottom_service_box_top_sizer->Add(service, 1, wxALL | wxEXPAND);
	////////////////////

	//ADDSERVICE
	wxBoxSizer* panel_main_top_service_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	add_service = new sm_Button(panel_main_bottom_service_box_bottom, &sm_UpdateBooking::add_service_to_list, this, wxDefaultSize, "Add>>");
	panel_main_bottom_service_box_bottom->SetSizer(panel_main_top_service_box_bottom_sizer);
	panel_main_top_service_box_bottom_sizer->Add(add_service, 1, wxALL | wxEXPAND);
	////////////////////
	//SERVICESLISTBOX
	wxBoxSizer* panel_main_bottom_services_list_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	services = new wxTextCtrl(panel_main_bottom_services_list_box, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	panel_main_bottom_services_list_box->SetSizer(panel_main_bottom_services_list_box_sizer);
	panel_main_bottom_services_list_box_sizer->Add(services, 1, wxALL | wxEXPAND);

	for (int i = 0; i < booking->getMservices().count(); i++)
	{
		services->AppendText(booking->getMservices()[i]->m_name + "\n");
	}
	services_list = booking->getMservices();
	////////////////////

	//DATESTART
	wxBoxSizer* panel_main_bottom_date_box_sizer = new wxBoxSizer(wxVERTICAL);
	panel_main_bottom_date_box->SetSizer(panel_main_bottom_date_box_sizer);
	sm_BasePanel* panel_main_bottom_date_box_top = new sm_BasePanel(panel_main_bottom_date_box, wxSize(-1, 50), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_date_box_bottom = new sm_BasePanel(panel_main_bottom_date_box, wxSize(-1, 50), tp_colour_misc::purple);
	panel_main_bottom_date_box_sizer->Add(panel_main_bottom_date_box_top, 1, wxALL | wxEXPAND);
	panel_main_bottom_date_box_sizer->Add(panel_main_bottom_date_box_bottom, 1, wxALL | wxEXPAND);
	////////////////////
	//DATESTRING
	wxBoxSizer* panel_main_bottom_date_box_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	datetime = new wxTextCtrl(panel_main_bottom_date_box_top, wxID_ANY, datetime_val.To_String(), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	panel_main_bottom_date_box_top->SetSizer(panel_main_bottom_date_box_top_sizer);
	panel_main_bottom_date_box_top_sizer->Add(datetime, 1, wxALL | wxEXPAND);
	////////////////////
	//DATEPICK
	wxBoxSizer* panel_main_bottom_date_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	get_date = new sm_Button(panel_main_bottom_date_box_bottom, &sm_UpdateBooking::get_date_picker, this, wxDefaultSize, "Get Timeslot");
	panel_main_bottom_date_box_bottom->SetSizer(panel_main_bottom_date_box_bottom_sizer);
	panel_main_bottom_date_box_bottom_sizer->Add(get_date, 1, wxALL | wxEXPAND);
	////////////////////

	//PAID CHECK
	wxBoxSizer* panel_main_paid_sizer = new wxBoxSizer(wxHORIZONTAL);
	sm_BasePanel* spacer1 = new sm_BasePanel(panel_main_paid, wxSize(-1, -1), tp_colour_menus::menu_white);
	paid = new wxCheckBox(panel_main_paid,wxID_ANY,"Paid?");
	sm_BasePanel* spacer2 = new sm_BasePanel(panel_main_paid, wxSize(-1, -1), tp_colour_menus::menu_white);
	panel_main_paid->SetSizer(panel_main_paid_sizer);
	panel_main_paid_sizer->Add(spacer1, 1, wxALL | wxEXPAND);
	panel_main_paid_sizer->Add(paid, 1, wxALL | wxEXPAND);
	panel_main_paid_sizer->Add(spacer2, 1, wxALL | wxEXPAND);
	paid->SetValue(booking->getMpaid());
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_UpdateBooking::update_booking, this, wxDefaultSize, "Update Booking");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////

	this->Show(true);
}

sm_UpdateBooking::~sm_UpdateBooking()
{
	created = false;
}


void sm_NewStaff::add_service_to_list(wxCommandEvent& event)
{
	services->AppendText(service->GetStringSelection() + "\n");
	services_list.add_back(data_handler::Get_Service_By_Name((std::string)service->GetStringSelection()));
}
void sm_NewStaff::get_hour_picker(wxCommandEvent& event)
{
	all_shifts.add_back();
	sm_NewStaff_ShiftBox::sm_GetShift<sm_NewStaff_ShiftBox>(&all_shifts[all_shifts.count() - 1], regular_hours->GetValue());
	
}
void sm_NewStaff::add_staff(wxCommandEvent& event)
{
	Staff stafftoadd(	(std::string)name->WXGetTextEntry()->GetValue(),
						(std::string)phone->WXGetTextEntry()->GetValue(),
						regular_hours->GetValue(),
						fixed_fee->GetValue(),
						std::stof((std::string)rate->WXGetTextEntry()->GetValue()),
						services_list, llist<Booking>(), all_shifts);
	data_handler::Add_Staff(stafftoadd);
	DEBUG_TRACE_CODE(
		std::string temp = "New Staff Added: " + data_handler::Get_Staff()[data_handler::Get_Staff().count() - 1].To_String();
	)
	LOG_TRACE(temp);

	UpdateStaffTimeslotsAt(data_handler::Get_Staff().count() - 1);
	Close();
}
sm_NewStaff* sm_NewStaff::instance = nullptr;
sm_NewStaff* sm_NewStaff::get()
{
	if (instance == nullptr)
	{
		instance = new sm_NewStaff();
	}
	return instance;
}

sm_NewStaff::sm_NewStaff() : SubFrame(Main_Event_Window::get(), 600, 350, tp_colour_menus::menu_black)
{
	
	instance = this;
	name = nullptr;
	phone = nullptr;
	fixed_fee = nullptr;
	rate = nullptr;
	regular_hours = nullptr;
	add_hour = nullptr;
	hours_list = nullptr;
	service = nullptr;
	services = nullptr;
	add_service = nullptr;
	finish = nullptr;
	wxBoxSizer* verti_sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(verti_sizer);
	sm_BasePanel* panel_main_top = new sm_BasePanel(this, wxSize(-1, 50), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_mid = new sm_BasePanel(this, wxSize(-1, 100), tp_colour_misc::red);
	sm_BasePanel* panel_main_bottom = new sm_BasePanel(this, wxSize(-1, 100), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::deep_blue);
	verti_sizer->Add(panel_main_top, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_mid, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_bottom, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_fin, 1, wxALL | wxEXPAND);

	//TOP PANEL WORKINGS
	wxBoxSizer* panel_main_top_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_top->SetSizer(panel_main_top_hori_sizer);
	sm_BasePanel* panel_main_top_name_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_top_phone_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_top_fixed_fee_box = new sm_BasePanel(panel_main_top, wxSize(-1, -1), tp_colour_misc::white);
	panel_main_top_hori_sizer->Add(panel_main_top_name_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_phone_box, 1, wxALL | wxEXPAND);
	panel_main_top_hori_sizer->Add(panel_main_top_fixed_fee_box, 1, wxALL | wxEXPAND);
	////////////////
	//NAME
	wxBoxSizer* panel_main_top_name_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	name = new wxTextCtrl(panel_main_top_name_box, wxID_ANY, "-Name");
	panel_main_top_name_box->SetSizer(panel_main_top_name_box_sizer);
	panel_main_top_name_box_sizer->Add(name, 1, wxALL | wxEXPAND);
	////////////////
	//PHONE
	wxBoxSizer* panel_main_top_phone_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	phone = new wxTextCtrl(panel_main_top_phone_box, wxID_ANY, "-Phone");
	panel_main_top_phone_box->SetSizer(panel_main_top_phone_box_sizer);
	panel_main_top_phone_box_sizer->Add(phone, 1, wxALL | wxEXPAND);
	////////////////////
	//FIXED_FEE
	wxBoxSizer* panel_main_top_fixed_fee_box_sizer = new wxBoxSizer(wxVERTICAL);
	fixed_fee = new wxCheckBox(panel_main_top_fixed_fee_box, wxID_ANY, "Fixed Fee?");
	panel_main_top_fixed_fee_box->SetSizer(panel_main_top_fixed_fee_box_sizer);
	panel_main_top_fixed_fee_box_sizer->Add(fixed_fee);
	////////////////////
	//RATE
	rate = new wxTextCtrl(panel_main_top_fixed_fee_box, wxID_ANY, "-Rate");
	panel_main_top_fixed_fee_box_sizer->Add(rate, 1, wxALL | wxEXPAND);
	////////////////////

	
	//MID PANEL WORKINGS
	wxBoxSizer* panel_main_mid_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_mid->SetSizer(panel_main_mid_hori_sizer);
	sm_BasePanel* panel_main_mid_regular_hours_box = new sm_BasePanel(panel_main_mid, wxSize(-1, -1), tp_colour_misc::white);
	sm_BasePanel* panel_main_mid_hours_list_box = new sm_BasePanel(panel_main_mid, wxSize(-1, -1), tp_colour_misc::grass_green);
	panel_main_mid_hori_sizer->Add(panel_main_mid_regular_hours_box, 1, wxALL | wxEXPAND);
	panel_main_mid_hori_sizer->Add(panel_main_mid_hours_list_box, 1, wxALL | wxEXPAND);
	////////////////
	
	//REGULAR HOURS
	wxBoxSizer* panel_main_mid_regular_hours_box_sizer = new wxBoxSizer(wxVERTICAL);
	regular_hours = new wxCheckBox(panel_main_mid_regular_hours_box, wxID_ANY, "Regular Hours?");
	panel_main_mid_regular_hours_box->SetSizer(panel_main_mid_regular_hours_box_sizer);
	panel_main_mid_regular_hours_box_sizer->Add(regular_hours);
	////////////////////
	//ADD_HOUR
	add_hour = new sm_Button(panel_main_mid_regular_hours_box, &sm_NewStaff::get_hour_picker, this, wxDefaultSize, "Add Shift");
	panel_main_mid_regular_hours_box_sizer->Add(add_hour, 1, wxALL | wxEXPAND);
	sm_BasePanel* spacer = new sm_BasePanel(panel_main_mid_regular_hours_box, wxSize(-1, -1), tp_colour_misc::white);
	panel_main_mid_regular_hours_box_sizer->Add(spacer, 1, wxALL | wxEXPAND);
	////////////////////
	//HOURSLISTBOX
	wxBoxSizer* panel_main_mid_hours_list_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	hours_list = new wxTextCtrl(panel_main_mid_hours_list_box, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	panel_main_mid_hours_list_box->SetSizer(panel_main_mid_hours_list_box_sizer);
	panel_main_mid_hours_list_box_sizer->Add(hours_list, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM PANEL WORKINGS
	wxBoxSizer* panel_main_bottom_hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	panel_main_bottom->SetSizer(panel_main_bottom_hori_sizer);
	sm_BasePanel* panel_main_bottom_service_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_services_list_box = new sm_BasePanel(panel_main_bottom, wxSize(-1, -1), tp_colour_misc::red);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_service_box, 1, wxALL | wxEXPAND);
	panel_main_bottom_hori_sizer->Add(panel_main_bottom_services_list_box, 1, wxALL | wxEXPAND);
	//ALLSERVICES
	wxBoxSizer* panel_main_bottom_service_box_sizer = new wxBoxSizer(wxVERTICAL);
	panel_main_bottom_service_box->SetSizer(panel_main_bottom_service_box_sizer);
	sm_BasePanel* panel_main_bottom_service_box_top = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	sm_BasePanel* panel_main_bottom_service_box_bottom = new sm_BasePanel(panel_main_bottom_service_box, wxSize(-1, 50), tp_colour_misc::purple);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_top, 1, wxALL | wxEXPAND);
	panel_main_bottom_service_box_sizer->Add(panel_main_bottom_service_box_bottom, 1, wxALL | wxEXPAND);
	//SERVICE
	wxArrayString serviceNames;

	serviceNames.Add("-Service"); // populate the array
	for (int i = 0; i < data_handler::Get_Services().count(); i++)
	{
		serviceNames.Add(data_handler::Get_Services()[i].m_name);
	}

	wxBoxSizer* panel_main_bottom_service_box_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	service = new wxChoice(panel_main_bottom_service_box_top, wxID_ANY, wxDefaultPosition, wxDefaultSize, serviceNames, 0);
	service->SetSelection(0);
	panel_main_bottom_service_box_top->SetSizer(panel_main_bottom_service_box_top_sizer);
	panel_main_bottom_service_box_top_sizer->Add(service, 1, wxALL | wxEXPAND);
	////////////////////

	//ADDSERVICE
	wxBoxSizer* panel_main_top_service_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	add_service = new sm_Button(panel_main_bottom_service_box_bottom, &sm_NewStaff::add_service_to_list, this, wxDefaultSize, "Add>>");
	panel_main_bottom_service_box_bottom->SetSizer(panel_main_top_service_box_bottom_sizer);
	panel_main_top_service_box_bottom_sizer->Add(add_service, 1, wxALL | wxEXPAND);
	////////////////////
	//SERVICESLISTBOX
	wxBoxSizer* panel_main_bottom_services_list_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	services = new wxTextCtrl(panel_main_bottom_services_list_box, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	panel_main_bottom_services_list_box->SetSizer(panel_main_bottom_services_list_box_sizer);
	panel_main_bottom_services_list_box_sizer->Add(services, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_NewStaff::add_staff, this, wxDefaultSize, "Add Staff");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////
	this->Show(true);
	
}


sm_NewService::sm_NewService() : SubFrame(Main_Event_Window::get(), 300, 250, tp_colour_menus::menu_black)
{
	name = nullptr;
	duration = nullptr;
	cost = nullptr;
	finish = nullptr;

	wxBoxSizer* verti_sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(verti_sizer);
	sm_BasePanel* panel_main_top = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_mid = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::red);
	sm_BasePanel* panel_main_bottom = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::grass_green);
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::deep_blue);
	verti_sizer->Add(panel_main_top, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_mid, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_bottom, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_fin, 1, wxALL | wxEXPAND);


	//NAME
	wxBoxSizer* panel_main_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	name = new wxTextCtrl(panel_main_top, wxID_ANY, "-Service Name");
	panel_main_top->SetSizer(panel_main_top_sizer);
	panel_main_top_sizer->Add(name, 1, wxALL | wxEXPAND);
	////////////////////

	//DURATION
	wxBoxSizer* panel_main_mid_sizer = new wxBoxSizer(wxHORIZONTAL);
	duration = new wxTextCtrl(panel_main_mid, wxID_ANY, "-Duration (mins)");
	panel_main_mid->SetSizer(panel_main_mid_sizer);
	panel_main_mid_sizer->Add(duration, 1, wxALL | wxEXPAND);
	////////////////////

	//COST
	wxBoxSizer* panel_main_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	cost = new wxTextCtrl(panel_main_bottom, wxID_ANY, "-Cost");
	panel_main_bottom->SetSizer(panel_main_bottom_sizer);
	panel_main_bottom_sizer->Add(cost, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_NewService::add_service, this, wxDefaultSize, "Add Service");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////
	this->Show(true);
}

void sm_NewService::add_service(wxCommandEvent& event)
{
	data_handler::Add_Service(service(	(std::string)name->WXGetTextEntry()->GetValue(),
										std::stoi((std::string)duration->WXGetTextEntry()->GetValue()),
										std::stof((std::string)cost->WXGetTextEntry()->GetValue())));
	DEBUG_TRACE_CODE(
		std::string temp = "New Service Added: " + data_handler::Get_Services()[data_handler::Get_Services().count()-1].m_name + " ";
		temp += std::to_string(data_handler::Get_Services()[data_handler::Get_Services().count()-1].m_duration) + " ";
		temp += std::to_string(data_handler::Get_Services()[data_handler::Get_Services().count()-1].m_cost);
		)
	LOG_TRACE(temp);
	Close();
}

void UpdateStaffTimeslotsAt(int index)
{
	Staff* staff = &data_handler::Get_Staff()[index];
	DateTime day = data_handler::Get_Selected_Date();
	DateTime day_end = day;
	day_end.setHour(24);
	llist<Booking*> bookings = staff->GetBookingsDuring(day,day_end);

	bool has_day = false;
	working_period shift;
	wxWindowList& windows = Main_Event_Window::get()->main_scroller->GetChildren();
	wxWindow* panel = windows[index];
	wxWindow* hours_box = panel->GetChildren()[1];
	if (staff->m_regular_hours)
	{
		for (int i = 0; i < staff->getHours().count(); i++)
		{
			if (staff->getHours()[i].m_day == (week_day)day.GetWeekDay())
			{
				has_day = true;
				shift = staff->getHours()[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < staff->getHours().count(); i++)
		{
			DateTime start = staff->getHours()[i].m_start;
			start.setHour(0);
			if (start == day)
			{
				has_day = true;
				shift = staff->getHours()[i];
			}
		}
	}
	if (has_day)
	{
		DateTime shift_start(day.getYear(),day.getMonth(),day.getDay(), shift.m_start.getHour(), shift.m_start.getMinute(),0);
		DateTime shift_finish(day.getYear(),day.getMonth(),day.getDay(), shift.m_finish.getHour(), shift.m_finish.getMinute(),0);
		llist<Booking*> bookings_in_shift = staff->GetBookingsDuring(shift_start, shift_finish);
		for (int i = 7; i < 22; i++)
		{
			sm_Slot_Button* slot = (sm_Slot_Button*)hours_box->GetChildren()[i - 7]->GetChildren()[1];
			if (i >= shift.m_start.getHour() && i < shift.m_finish.getHour())
			{
				if (bookings_in_shift.count() > 0)
				{
					for (int j = 0; j < bookings_in_shift.count(); j++)
					{
						if (i >= bookings_in_shift[j]->getMtimeSlot().getHour() && i < bookings_in_shift[j]->getMtimeSlot().getHour() + ceil((float)bookings_in_shift[j]->FullServiceDuration() / 60.0f))
						{
							if (bookings_in_shift[j]->getMpaid())
							{
								slot->SetBackgroundColour(tp_colour_log::trace);
							}
							else
							{
								slot->SetBackgroundColour(tp_colour_log::warning);
							}
							;
							slot->booking = bookings_in_shift[j];
							break;
						}
						else
						{
							slot->SetBackgroundColour(tp_colour_log::light);
							slot->booking = nullptr;
						}
					}
				}
				else
				{
					slot->SetBackgroundColour(tp_colour_log::light);
					slot->booking = nullptr;
				}
			}
			else
			{
				slot->SetBackgroundColour(tp_colour_misc::black);
				slot->booking = nullptr;
			}
		}
	}
	else
	{
		for (int i = 7; i < 22; i++)
		{
			hours_box->GetChildren()[i - 7]->GetChildren()[1]->SetBackgroundColour(tp_colour_misc::black);
		}
	}
	
}

void sm_Earnings::view_earnings(wxCommandEvent& event)
{
	LOG_LINE("===========================================");
	LOG_LINE("-----EARNINGS-----");
	int total_paid=0;
	int total_all=0;
	int indiv_paid;
	int indiv_all;
	int indiv_contr_paid;
	int indiv_contr_all;
	int hours;
	DateTime start_date(start->GetDate().GetYear(),start->GetDate().GetMonth()+1,start->GetDate().GetDay(),0,0);
	DateTime end_date(end->GetDate().GetYear(), end->GetDate().GetMonth() + 1, end->GetDate().GetDay(), 0, 0);
	LOG_LINE("From: "+start_date.To_String_Date());
	LOG_LINE("To: "+end_date.To_String_Date());

	for (int i = 0; i < data_handler::Get_Staff().count(); i++)
	{
		indiv_paid = 0;
		indiv_all = 0;
		indiv_contr_paid = 0;
		indiv_contr_all = 0;
		hours = 0;
		Staff* staff = &data_handler::Get_Staff()[i];
		llist<Booking*> bookings_in_period = staff->GetBookingsDuring(start_date, end_date);
		for (int j = 0; j < bookings_in_period.count(); j++)
		{
			Booking* booking = bookings_in_period[j];
			for (int k = 0; k < booking->getMservices().count(); k++)
			{
				indiv_all+=booking->getMservices()[k]->m_cost;
				if (booking->getMpaid())
				{
					indiv_paid+=booking->getMservices()[k]->m_cost;
				}
			}
		}
		if (staff->m_fixed_fee)
		{
			if (staff->m_regular_hours)
			{
				time_t start_secs = start_date.to_time_t();
				time_t end_secs = end_date.to_time_t();

				int secs_difference = end_secs - start_secs;
				int days_difference = secs_difference / (60 * 60 * 24);

				int day = start_date.to_tm()->tm_wday==0?6: start_date.to_tm()->tm_wday-1;
				for (int j = 0; j < days_difference; j++)
				{
					if (day == 7)
						day = 0;
					
					for (int k = 0; k < staff->getHours().count(); k++)
					{
						working_period shift = staff->getHours()[k];
						if ((int)shift.m_day == day)
						{
							hours += shift.m_finish.getHour() - shift.m_start.getHour();
						}
					}

					day++;
				}

			}
			else
			{
				for (int j = 0; j < staff->getHours().count(); j++)
				{
					working_period shift = staff->getHours()[j];
					if (shift.m_start >= start_date && shift.m_start <= end_date)
					{
						hours += shift.m_finish.getHour() - shift.m_start.getHour();
					}
				}
			}
			indiv_contr_paid += hours * staff->m_rate;
			indiv_contr_all += hours * staff->m_rate;
		}
		else
		{
			indiv_contr_paid += indiv_paid * (staff->m_rate / 100);
			indiv_contr_all += indiv_all * (staff->m_rate / 100);
		}

		total_all += indiv_contr_all;
		total_paid += indiv_contr_paid;
		LOG_LINE(staff->m_name + ": ");
		LOG_LINE("    Rate:    "+(staff->m_fixed_fee? "\u00A3" :"")+std::to_string(staff->m_rate)+ (staff->m_fixed_fee ? " per hour" : "%"));
		if (staff->m_fixed_fee)
		{
			LOG_LINE("    Hours Worked: " + std::to_string(hours));
		}
		LOG_LINE("    Gross:    "+std::to_string(indiv_paid));
		LOG_LINE("    Forecast: "+std::to_string(indiv_all));
		LOG_LINE("    Gross Contribution: "+std::to_string(indiv_contr_paid));
		LOG_LINE("    Forecast Contribution: "+std::to_string(indiv_contr_all));
		LOG_LINE("-------------------------------------------");
	}
	LOG_LINE("===========================================");
	LOG_LINE("    Gross Earnings:    "+std::to_string(total_paid));
	LOG_LINE("    Forecast Earnings:    "+std::to_string(total_all));
	
	CONSOLE::Get()->SetFocus();

	Close();
}

sm_Earnings::sm_Earnings() : SubFrame(Main_Event_Window::get(), 500, 250, tp_colour_menus::menu_black)
{
	start = nullptr;
	end = nullptr;
	finish = nullptr;
	
	wxBoxSizer* verti_sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(verti_sizer);
	sm_BasePanel* panel_main_top = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::cyan);
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this, wxSize(-1, -1), tp_colour_misc::deep_blue);
	verti_sizer->Add(panel_main_top, 1, wxALL | wxEXPAND);
	verti_sizer->Add(panel_main_fin, 1, wxALL | wxEXPAND);

	//DATES
	wxBoxSizer* panel_main_top_sizer = new wxBoxSizer(wxHORIZONTAL);
	start = new wxCalendarCtrl(panel_main_top,wxID_ANY);
	end = new wxCalendarCtrl(panel_main_top,wxID_ANY);
	panel_main_top->SetSizer(panel_main_top_sizer);
	panel_main_top_sizer->Add(start, 1, wxALL | wxEXPAND);
	panel_main_top_sizer->Add(end, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_Earnings::view_earnings, this, wxDefaultSize, "View Earnings");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////
	this->Show(true);
}
