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

wxBasePanel::wxBasePanel(wxWindow* window, wxSize size, wxColour colour, int style) : wxWindow(window,wxID_ANY,wxDefaultPosition,wxDefaultSize,style)
{
	this->SetBackgroundColour(colour);
	if (size != wxDefaultSize) {
		this->SetMaxSize(size);
		this->SetMinSize(size);
	}
}

wxBooking::wxBooking(wxWindow* window, wxSize size, wxColour colour, int style) : wxBasePanel(window,size,colour,style)
{
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