#include <iostream>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/menu.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/msgdlg.h>
#include <wx/button.h>
#include <wxRelPanel.h>


wxRelPanel::wxRelPanel() {}
wxRelPanel::wxRelPanel(wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name)
{
    Create(parent, id, pos, size, style, name);
}

wxRelPanel::~wxRelPanel() {}

void wxRelPanel::Resize(wxSize s)
{
    wxPoint curPos;
    this->GetPosition(&(curPos.x), &(curPos.y));
    this->SetPosition(wxPoint(s.x-this->size.x,curPos.y));
}