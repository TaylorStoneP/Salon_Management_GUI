#pragma once
#include <wx/window.h>
class sm_row_array_pane;
class ScrolledWidgetsPane;
class MyApp : public wxApp
{
private:
    int width = 0;
    int height = 0;
public:
    wxFrame* mainWin = nullptr;
	virtual bool OnInit();
    wxSize WinSize();
    int Width();
    int Height();
};

class Main_Event_Window : public wxFrame
{
    static Main_Event_Window* m_instance;
public:
    ScrolledWidgetsPane* main_scroller;
    wxWindow* main_win;
    Main_Event_Window(MyApp* app);
    //Can only be called once there is a main window.
    static Main_Event_Window* get();
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEDIT_FLIP(wxCommandEvent& event);
    void OnEDIT_MOVE(wxCommandEvent& event);
    void OnEDIT_FILTERS(wxCommandEvent& event);

    void add_row(wxCommandEvent& event);
    void add_row();
    void remove_row(wxCommandEvent& event);

    void add_booking(wxCommandEvent& event);
    void add_service(wxCommandEvent& event);
    void add_staff(wxCommandEvent& event);
    void change_date(wxCommandEvent& event);
    void save(wxCommandEvent& event);
    void load(wxCommandEvent& event);
    //void add_staff(wxCommandEvent& event);
};

class SubFrame : public wxFrame
{
public:
    SubFrame(wxWindow* window, int width, int height, wxColour colour);
};

enum
{
    ID_Hello = 1, ID_EDIT_FLIP, ID_EDIT_MOVE, ID_EDIT_FILTERS, ADD
};