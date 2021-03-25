#pragma once
class wxRelPanel : public wxWindow
{
public:
	wxSize size;
	void Resize(wxSize s);
    wxRelPanel();

    wxRelPanel(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxASCII_STR(wxPanelNameStr));

    virtual ~wxRelPanel();

};