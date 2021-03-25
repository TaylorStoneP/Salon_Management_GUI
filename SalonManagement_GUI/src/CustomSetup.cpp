
#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/menu.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wxRelPanel.h>
#include <CustomSetup.h>
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <basePanel.h>
#include <extraColours.h>

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
MyFrame::MyFrame(MyApp* app) : wxFrame(NULL, wxID_ANY, "Hello World",wxDefaultPosition,wxSize(1920,1080))
{
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

    wxBasePanel* main = new wxBasePanel(this,wxDefaultSize, tp_colour_menus::menu_black, wxBORDER_RAISED);
    wxBasePanel* left = new wxBasePanel(this, wxSize(200, -1), tp_colour_menus::menu_white, wxBORDER_RAISED);
    wxBasePanel* right = new wxBasePanel(this, wxSize(200, -1), tp_colour_menus::menu_white, wxBORDER_RAISED);
    
    topsizer->Add(left,1, wxALL|wxEXPAND);
    topsizer->Add(main, 1, wxALL|wxEXPAND);
    topsizer->Add(right, 1, wxALL|wxEXPAND);
    SetSizer(topsizer);
    /*
    wxButton* button = new wxButton(this, wxID_ADD,"One");
    wxButton* button2 = new wxButton(this, wxID_ADD, "Two",wxPoint(wxDefaultPosition.x,wxButton::GetDefaultSize(button).y));
    wxButton* button3 = new wxButton(this, wxID_ADD, "Three", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*2));
    wxButton* button4 = new wxButton(this, wxID_ADD, "Four", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*3));
    wxButton* button5 = new wxButton(this, wxID_ADD, "Five", wxPoint(wxDefaultPosition.x, wxButton::GetDefaultSize(button).y*4));
    */
    
    CreateStatusBar();

    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnEDIT_FLIP, this, ID_EDIT_FLIP);
    Bind(wxEVT_MENU, &MyFrame::OnEDIT_MOVE, this, ID_EDIT_MOVE);
    Bind(wxEVT_MENU, &MyFrame::OnEDIT_FILTERS, this, ID_EDIT_FILTERS);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnEDIT_FLIP(wxCommandEvent& event)
{
    wxMessageBox("Selection flipped.",
        "Flip", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnEDIT_MOVE(wxCommandEvent& event)
{
    SubFrame* subframe = new SubFrame(this, 1920, 1080, wxColour(255, 0, 255));
    subframe->ShowFullScreen(true);
}
void MyFrame::OnEDIT_FILTERS(wxCommandEvent& event)
{
    wxMessageBox("Filters list...",
        "Filters", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

SubFrame::SubFrame(wxWindow* window, int width, int height, wxColour colour)
    : wxFrame(window, wxID_ANY, "", wxDefaultPosition, wxSize(width, height))
{
    this->SetBackgroundColour(colour);
}