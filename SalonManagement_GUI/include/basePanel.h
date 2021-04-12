
#ifndef BASEPANEL_H
#define BASEPANEL_H
#include <wx/wx.h>
#include "Staff.h"
#include "llist.h"
#include "CustomSetup.h"
#include <wx/calctrl.h>

void UpdateStaffTimeslotsAt(int index);

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

class sm_Slot_Button : public sm_Button
{
	const int time_slot;
	Staff* staff;
public:
	sm_Slot_Button(wxWindow* window, wxSize size = wxDefaultSize, wxString text = "", int time = -1, Staff* staff=nullptr) :sm_Button(window, &sm_Slot_Button::get_booking, this, size, text), time_slot(time), staff(staff)
	{}
	void get_booking(wxCommandEvent& event) {}
};

void UpdateStaffTimeslotsAt(int index);

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


public:
	sm_StaffBookingPanel(wxWindow* parent, int staff_index);
};

class sm_DateTimeBox : public SubFrame
{
public:

	wxCalendarCtrl* calendar;
	wxChoice* hour;
	wxChoice* minute;
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

class sm_ShiftBox : public SubFrame
{
public:
	bool alternate;
	wxCalendarCtrl* calendar;
	wxChoice* weekday;
	wxChoice* start_hour;
	wxChoice* start_minute;
	wxChoice* finish_hour;
	wxChoice* finish_minute;
	sm_Button* finish;
	working_period* shift;
	sm_ShiftBox(bool alternate);
	void SetShift(wxCommandEvent& event);
	template <typename Class>
	static void sm_GetShift(working_period* shift, bool alternate)
	{
		Class* form = new Class(alternate);
		form->shift = shift;
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
	static bool created;
	static sm_NewBooking* instance;
	DateTime datetime_val;
	void add_service_to_list(wxCommandEvent& event);
	void get_date_picker(wxCommandEvent& event);
	void add_booking_to_staff(wxCommandEvent& event);
public:
	static sm_NewBooking* get();
	llist<service*> services_list;
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
	~sm_NewBooking();
};

class sm_NewStaff : public SubFrame
{
	class sm_NewStaff_ShiftBox : public sm_ShiftBox
	{
	public:
		sm_NewStaff_ShiftBox(bool alternate) :sm_ShiftBox(alternate) {}
		void Extra() override
		{
			get()->hours_list->AppendText(get()->all_shifts[get()->all_shifts.count()-1].To_String(alternate)+"\n");
		}

	};

	static sm_NewStaff* instance;
	void add_service_to_list(wxCommandEvent& event);
	void get_hour_picker(wxCommandEvent& event);
	void add_staff(wxCommandEvent& event);
	
public:
	llist<working_period> all_shifts;
	llist<service*> services_list;
	static sm_NewStaff* get();
	wxTextCtrl* name;
	wxTextCtrl* phone;
	wxCheckBox* fixed_fee;
	wxTextCtrl* rate;
	wxCheckBox* regular_hours;
	sm_Button* add_hour;
	wxTextCtrl* hours_list;
	wxChoice* service;
	wxTextCtrl* services;
	sm_Button* add_service;
	sm_Button* finish;
	sm_NewStaff();


};

class sm_NewService : public SubFrame
{
	wxTextCtrl* name;
	wxTextCtrl* duration;
	wxTextCtrl* cost;
	sm_Button* finish;
public:
	sm_NewService();
	void add_service(wxCommandEvent& event);
};

#endif