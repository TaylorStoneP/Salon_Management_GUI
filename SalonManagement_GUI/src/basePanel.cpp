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

sm_StaffBookingPanel::sm_StaffBookingPanel(wxWindow* parent, int staff_index):sm_BasePanel(parent,wxSize(parent->GetClientSize().GetX(),50)),staff(nullptr)
{
	Staff& staff_in = data_handler::Get_Staff()[staff_index];
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
	wxTextCtrl* staff_text = new wxTextCtrl(staff_box,wxID_ANY,staff_in.m_name,wxDefaultPosition,wxDefaultSize, wxTE_CENTRE| wxTE_READONLY| wxTE_MULTILINE| wxTE_NO_VSCROLL);
	box_filler->Add(staff_text,1, wxALL | wxEXPAND);
	//total_width += unit_width * 1.5f;
	
	sm_BasePanel* hours_box = new sm_BasePanel(this, wxSize(this->GetClientSize().GetX()-staff_box->GetClientSize().GetWidth(),unit_height),tp_colour_menus::menu_grey, wxSUNKEN_BORDER);
	hori_sizer->Add(hours_box, 1, wxALL | wxEXPAND);

	wxBoxSizer* hours_box_sizer = new wxBoxSizer(wxHORIZONTAL);
	hours_box->SetSizer(hours_box_sizer);

	LOG_TRACE(std::to_string(staff_box->GetClientSize().GetWidth()));
	LOG_TRACE(std::to_string(hours_box->GetClientSize().GetWidth()));
	LOG_TRACE(std::to_string(parent->GetSize().GetWidth()));
	wxSize unit_size(hours_box->GetMaxSize().x/14, unit_height);
	wxSize sub_unit_size(-1, unit_height/2);
	for (int i = 7; i < 21; i++)
	{
		sm_BasePanel* unit = new sm_BasePanel(hours_box, unit_size,tp_colour_menus::menu_grey);
		wxBoxSizer* indiv_dual = new wxBoxSizer(wxVERTICAL);

		sm_BasePanel* hour = new sm_BasePanel(unit, sub_unit_size,tp_colour_menus::menu_black);
		wxTextCtrl* hour_text = new wxTextCtrl(hour,wxID_ANY,std::to_string(i), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE | wxTE_READONLY | wxTE_MULTILINE | wxTE_NO_VSCROLL);
		wxBoxSizer* box_filler_hour = new wxBoxSizer(wxHORIZONTAL);
		box_filler_hour->Add(hour_text, 1, wxALL | wxEXPAND);
		hour->SetSizer(box_filler_hour);

		sm_BasePanel* slot = new sm_BasePanel(unit, sub_unit_size,(i>=7&&i<=17?(random::GetInstance()->rand_int(0,1)==0? tp_colour_menus::menu_white:tp_colour_log::error):tp_colour_misc::black));
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
	second = new wxChoice(hour_slot, wxID_ANY,wxDefaultPosition, wxDefaultSize, myChoicesMinSec, 0);
	second->SetSelection(0);
	hour_slot_sizer->Add(hour, 1, wxALL | wxEXPAND);
	hour_slot_sizer->Add(minute, 1, wxALL | wxEXPAND);
	hour_slot_sizer->Add(second, 1, wxALL | wxEXPAND);
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
	int month = calendar->GetDate().GetMonth();
	int day = calendar->GetDate().GetDay();
	*date = DateTime(year, month, day, hour->GetSelection(), minute->GetSelection());
	Extra();
	this->Close();
}

void sm_NewBooking::add_service_to_list(wxCommandEvent& event)
{
	services->AppendText(service->GetStringSelection()+"\n");
}
void sm_NewBooking::get_date_picker(wxCommandEvent& event)
{
	sm_NewBooking_DateTimeBox::sm_GetDateTime<sm_NewBooking_DateTimeBox>(&datetime_val);
}
sm_NewBooking* sm_NewBooking::instance = nullptr;
sm_NewBooking* sm_NewBooking::get()
{
	if (instance == nullptr)
	{
		instance = new sm_NewBooking();
	}
	return instance;
}

sm_NewBooking::sm_NewBooking(): SubFrame(Main_Event_Window::get(), 500, 300, tp_colour_menus::menu_black)
{
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
	sm_BasePanel* panel_main_fin = new sm_BasePanel(this,wxSize(-1,50),tp_colour_misc::deep_blue);
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
	staffNames.Add("Bruce Wayne"); // populate the array
	staffNames.Add("Clark Kent"); // populate the array
	staffNames.Add("Peter Parker"); // populate the array
	
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
	serviceNames.Add("Cut"); // populate the array
	serviceNames.Add("Wash"); // populate the array
	serviceNames.Add("Trim"); // populate the array
	serviceNames.Add("Dye"); // populate the array

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
	//ADDSERVICE
	wxBoxSizer* panel_main_bottom_date_box_bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
	get_date = new sm_Button(panel_main_bottom_date_box_bottom, &sm_NewBooking::get_date_picker, this, wxDefaultSize, "Get Timeslot");
	panel_main_bottom_date_box_bottom->SetSizer(panel_main_bottom_date_box_bottom_sizer);
	panel_main_bottom_date_box_bottom_sizer->Add(get_date, 1, wxALL | wxEXPAND);
	////////////////////

	//BOTTOM BUTTON
	wxBoxSizer* panel_main_fin_sizer = new wxBoxSizer(wxHORIZONTAL);
	finish = new sm_Button(panel_main_fin, &sm_NewBooking::get_date_picker, this, wxDefaultSize, "Add Booking");
	panel_main_fin->SetSizer(panel_main_fin_sizer);
	panel_main_fin_sizer->Add(finish, 1, wxALL | wxEXPAND);
	////////////////////

	this->Show(true);
}

