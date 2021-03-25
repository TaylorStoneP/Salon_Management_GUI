#pragma once
#include <wx/window.h>
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

class MyFrame : public wxFrame
{
public:
    MyFrame(MyApp* app);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEDIT_FLIP(wxCommandEvent& event);
    void OnEDIT_MOVE(wxCommandEvent& event);
    void OnEDIT_FILTERS(wxCommandEvent& event);
};

class SubFrame : public wxFrame
{
public:
    SubFrame(wxWindow* window, int width, int height, wxColour colour);
};

enum
{
    ID_Hello = 1, ID_EDIT_FLIP, ID_EDIT_MOVE, ID_EDIT_FILTERS
};