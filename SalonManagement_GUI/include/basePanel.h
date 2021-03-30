#pragma once
#include <wx/wx.h>
#include "Staff.h"
#include "llist.h"
#include "CustomSetup.h"
class sm_BasePanel : public wxWindow
{
public:
	sm_BasePanel(wxWindow* window, wxSize size = wxDefaultSize, wxColour colour = wxColour(255,0,255),int style = wxBORDER_DEFAULT);
};

class sm_Booking : public sm_BasePanel
{
public:
	wxTextCtrl* name;
	wxTextCtrl* phone;
	wxComboBox* service;
	wxButton* done;
	sm_Booking(wxWindow* window, wxSize size = wxDefaultSize, wxColour colour = wxColour(255, 0, 255), int style = wxBORDER_DEFAULT);
};

class sm_Button : public wxButton
{
public:
	//template<typename Class, typename EventArg>
	sm_Button(wxWindow* window, void (Main_Event_Window::* method)(wxCommandEvent&), wxSize size = wxDefaultSize, wxString text = ""):wxButton(window,wxID_ANY,text)
	{
		if (size != wxDefaultSize) {
			this->SetMaxSize(size);
			this->SetMinSize(size);
		}
		Bind(wxEVT_BUTTON, method, Main_Event_Window::get());
	}
};

class ScrolledWidgetsPane : public wxScrolledWindow
{
    wxBoxSizer* sizer;
	void update();

public:
	ScrolledWidgetsPane(wxWindow* parent, wxWindowID id);

	void add_widget(wxWindow* widget);

	void remove_widget(int index);
};

class sm_row_array_pane : public sm_BasePanel
{
	wxBoxSizer* sizer;
	void update();

public:
	sm_row_array_pane(wxWindow* parent);

	void add_widget(wxWindow* widget);

	void remove_widget(int index);
};

class sm_StaffBookingPanel : public sm_BasePanel
{
    Staff* staff;
    DateTime current_date;

public:
	sm_StaffBookingPanel(wxWindow* parent);
};