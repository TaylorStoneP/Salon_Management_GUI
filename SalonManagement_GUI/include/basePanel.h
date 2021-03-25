#pragma once

class wxBasePanel : public wxWindow
{
public:
	wxBasePanel(wxWindow* window, wxSize size = wxDefaultSize, wxColour colour = wxColour(255,0,255),int style = wxBORDER_DEFAULT);
};

class wxBooking : public wxBasePanel
{
public:
	wxTextCtrl* name;
	wxTextCtrl* phone;
	wxComboBox* service;
	wxButton* done;
	wxBooking(wxWindow* window, wxSize size = wxDefaultSize, wxColour colour = wxColour(255, 0, 255), int style = wxBORDER_DEFAULT);
};