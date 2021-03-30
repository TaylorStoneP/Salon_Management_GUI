#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/menu.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <basePanel.h>
#include "random.h"
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

sm_StaffBookingPanel::sm_StaffBookingPanel(wxWindow* parent):sm_BasePanel(parent,wxSize(parent->GetClientSize().GetX(),50)),staff(nullptr)
{
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
	wxTextCtrl* staff_text = new wxTextCtrl(staff_box,wxID_ANY,"name",wxDefaultPosition,wxDefaultSize, wxTE_CENTRE| wxTE_READONLY| wxTE_MULTILINE| wxTE_NO_VSCROLL);
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