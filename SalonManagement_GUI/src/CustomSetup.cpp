
#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/menu.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wxRelPanel.h>
#include <basePanel.h>
#include <CustomSetup.h>
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <extraColours.h>
#include "data_handler.h"

wxSize MyApp::WinSize()
{
    mainWin->GetSize(&width,&height);
    return { width,height };
}
int MyApp::Width()
{
    mainWin->GetSize(&width, &height);
    return width;
}
int MyApp::Height()
{
    mainWin->GetSize(&width, &height);
    return height;
}
Main_Event_Window::Main_Event_Window(MyApp* app) : wxFrame(NULL, wxID_ANY, "Hello World",wxDefaultPosition,wxSize(1920,1080))
{
    m_instance = this;
    this->Maximize();
    app->mainWin = this;
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append(ID_EDIT_FLIP, "&Flip",
        "Flips current selection.");
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_EDIT_MOVE, "&Move",
        "Moves current selection.");
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_EDIT_FILTERS, "&Filters",
        "Filters menu");
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEdit, "&Edit");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    wxBoxSizer* topsizer = new wxBoxSizer(wxHORIZONTAL);

    sm_BasePanel* main = new sm_BasePanel(this,wxDefaultSize, tp_colour_menus::menu_black, wxBORDER_RAISED);
    sm_BasePanel* left = new sm_BasePanel(this, wxSize(200, -1), tp_colour_menus::menu_white, wxBORDER_RAISED);
    sm_BasePanel* right = new sm_BasePanel(this, wxSize(200, -1), tp_colour_menus::menu_white, wxBORDER_RAISED);
    
    topsizer->Add(left,1, wxALL|wxEXPAND);
    topsizer->Add(main, 1, wxALL|wxEXPAND);
    topsizer->Add(right, 1, wxALL|wxEXPAND);
    SetSizer(topsizer);
    /*
    wxButton* button2 = new wxButton(this, wxID_ADD, "Two",wxPoint(wxDefaultPosition.x,wxButton::GetDefaultSize(button).y));
    wxButton* button3 = new wxButton(this, wxID_ADD, "Three", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*2));
    wxButton* button4 = new wxButton(this, wxID_ADD, "Four", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*3));
    wxButton* button5 = new wxButton(this, wxID_ADD, "Five", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*4));
    */
    
    
    wxBoxSizer* button_sizer = new wxBoxSizer(wxVERTICAL);
    sm_Button* button_add = new sm_Button(left,&Main_Event_Window::add_row, Main_Event_Window::get(),wxSize(-1, 40),"Add");
    sm_Button* button_remove = new sm_Button(left,&Main_Event_Window::remove_row, Main_Event_Window::get(), wxSize(-1, 40),"Remove");
    sm_Button* button_add_service = new sm_Button(left,&Main_Event_Window::add_service, Main_Event_Window::get(),wxSize(-1, 40),"Add Service");
    sm_Button* button_add_staff = new sm_Button(left,&Main_Event_Window::add_staff, Main_Event_Window::get(),wxSize(-1, 40),"Add Staff");
    sm_Button* button_add_booking = new sm_Button(left,&Main_Event_Window::add_booking, Main_Event_Window::get(),wxSize(-1, 40),"Add Booking");

    button_sizer->Add(button_add, 1, wxALL | wxEXPAND);
    button_sizer->Add(button_remove, 1, wxALL | wxEXPAND);
    button_sizer->Add(button_add_service, 1, wxALL | wxEXPAND);
    button_sizer->Add(button_add_staff, 1, wxALL | wxEXPAND);
    button_sizer->Add(button_add_booking, 1, wxALL | wxEXPAND);
    left->SetSizer(button_sizer);

    wxBoxSizer* scrollSize = new wxBoxSizer(wxHORIZONTAL);
    main_scroller = new ScrolledWidgetsPane(main,-1);

    scrollSize->Add(main_scroller, 1, wxEXPAND);
    main->SetSizer(scrollSize);

    CreateStatusBar();

    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &Main_Event_Window::OnHello, Main_Event_Window::get(), ID_Hello);
    Bind(wxEVT_MENU, &Main_Event_Window::OnEDIT_FLIP, Main_Event_Window::get(), ID_EDIT_FLIP);
    Bind(wxEVT_MENU, &Main_Event_Window::OnEDIT_MOVE, Main_Event_Window::get(), ID_EDIT_MOVE);
    Bind(wxEVT_MENU, &Main_Event_Window::OnEDIT_FILTERS, Main_Event_Window::get(), ID_EDIT_FILTERS);
    Bind(wxEVT_MENU, &Main_Event_Window::OnAbout, Main_Event_Window::get(), wxID_ABOUT);
    Bind(wxEVT_MENU, &Main_Event_Window::OnExit, Main_Event_Window::get(), wxID_EXIT);
}



void Main_Event_Window::add_row(wxCommandEvent& event)
{
    main_scroller->add_widget(new sm_StaffBookingPanel(main_scroller, data_handler::Get_Staff().count() - 1));
    //unit->Show(true);
}
void Main_Event_Window::remove_row(wxCommandEvent& event)
{
    main_scroller->remove_widget(0);
}

void Main_Event_Window::add_booking(wxCommandEvent& event)
{
    sm_NewBooking* newB = sm_NewBooking::get();
}
void Main_Event_Window::add_service(wxCommandEvent& event)
{
    sm_NewService* newS = new sm_NewService();
}
void Main_Event_Window::add_staff(wxCommandEvent& event)
{
    sm_NewStaff* newS = new sm_NewStaff();
}
void Main_Event_Window::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void Main_Event_Window::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void Main_Event_Window::OnEDIT_FLIP(wxCommandEvent& event)
{
    wxMessageBox("Selection flipped.",
        "Flip", wxOK | wxICON_INFORMATION);
}
void Main_Event_Window::OnEDIT_MOVE(wxCommandEvent& event)
{
    SubFrame* subframe = new SubFrame(this, 1920, 1080, wxColour(255, 0, 255));
    subframe->ShowFullScreen(true);
}
void Main_Event_Window::OnEDIT_FILTERS(wxCommandEvent& event)
{
    wxMessageBox("Filters list...",
        "Filters", wxOK | wxICON_INFORMATION);
}

void Main_Event_Window::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

SubFrame::SubFrame(wxWindow* window, int width, int height, wxColour colour)
    : wxFrame(window, wxID_ANY, "", wxDefaultPosition, wxSize(width, height))
{
    this->SetBackgroundColour(colour);
}

Main_Event_Window* Main_Event_Window::m_instance = nullptr;
Main_Event_Window* Main_Event_Window::get()
{
    return m_instance;
}