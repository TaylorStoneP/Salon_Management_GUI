#pragma once
#include <wx/wx.h>
#include "Staff.h"
#include "llist.h"
#include "CustomSetup.h"
#include <wx/calctrl.h>
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
	template<typename Class, typename Handler>// typename EventArg>
	sm_Button(wxWindow* window, void (Class::* method)(wxCommandEvent&), Handler handler, wxSize size = wxDefaultSize, wxString text = ""):wxButton(window,wxID_ANY,text)
	{
		if (size != wxDefaultSize) {
			this->SetMaxSize(size);
			this->SetMinSize(size);
		}
		Bind(wxEVT_BUTTON, method, handler);
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
	sm_StaffBookingPanel(wxWindow* parent, int staff_index);
};

class sm_DateTimeBox : public SubFrame
{
public:

	wxCalendarCtrl* calendar;
	wxChoice* hour;
	wxChoice* minute;
	wxChoice* second;
	sm_Button* finish;
	DateTime* date;
	sm_DateTimeBox();
	void SetDate(wxCommandEvent& event);
	template <typename Class>
	static void sm_GetDateTime(DateTime* date)
	{
		Class* form = new Class();
		form->date = date;
	}
	virtual void Extra();
};


class sm_NewBooking : public SubFrame
{
	class sm_NewBooking_DateTimeBox : public sm_DateTimeBox
	{
	public:
		void Extra() override
		{
			get()->datetime->Clear();
			get()->datetime->AppendText(get()->datetime_val.To_String());
		}

	};

	static sm_NewBooking* instance;
	DateTime datetime_val;
	void add_service_to_list(wxCommandEvent& event);
	void get_date_picker(wxCommandEvent& event);
public:
	static sm_NewBooking* get();
	wxTextCtrl*		name;
	wxTextCtrl*		phone;
	wxChoice*		staff;
	wxChoice*		service;
	wxTextCtrl*		services;
	sm_Button*		add_service;
	wxTextCtrl*		datetime;
	sm_Button*		get_date;
	sm_Button*		finish;

	sm_NewBooking();
	
};